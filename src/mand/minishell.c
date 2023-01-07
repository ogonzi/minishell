/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:51:36 by ogonzale          #+#    #+#             */
/*   Updated: 2023/01/07 18:21:46 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

/*
void	print_list(t_list *lst)
{
	t_list	*lst_cpy;
	t_list	*word_cpy;

	lst_cpy = lst;
	while (lst_cpy)
	{
		word_cpy = ((t_cmd_line_content *)lst_cpy->content)->word;
		printf("%s\n", ((t_cmd_line_content *)lst_cpy->content)->cmd);
		while (word_cpy)
		{
			printf("\t%s (%d)\n", ((t_token_content *)word_cpy->content)->word,
				((t_token_content *)word_cpy->content)->type);
			word_cpy = word_cpy->next;
		}
		lst_cpy = lst_cpy->next;
	}
	lst_cpy = 0;
}
*/

static void	custom_getpid(t_prompt *prompt)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		terminate(ERR_FORK, 1);
	if (pid == 0)
		exit(1);
	waitpid(pid, NULL, 0);
	prompt->pid = pid - 1;
}

static int	handle_input(t_prompt *prompt)
{
	char	*buf;
	int		err;

	buf = readline("msh> ");
	if (buf == NULL)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		return (-1);
	}
	if (ft_strlen(buf) != 0)
	{
		add_history(buf);
		err = split_cmd_line(prompt, buf);
		if (err != 0)
			return (free_and_return_error_code(&buf, err));
		err = split_words(prompt);
		if (err != 0)
			return (free_and_return_error_code(&buf, err));
		err = expand_words(prompt);
		if (err != 0)
			return (free_and_return_error_code(&buf, err));
	}
	free(buf);
	buf = NULL;
	return (0);
}

static void	init_prompt(t_prompt *prompt, char *argv[], char *envp[])
{
	prompt->cmd_line = NULL;
	prompt->environ = NULL;
	prompt->exit_status = 0;
	custom_getpid(prompt);
	set_environ(prompt, envp);
	init_env_vars(prompt, argv);
}

/**
 * Duplicates standard input & output to tmp_fd. This is done to
 * be able to implement redirections if necessary.
 * Loops through each pipe, calling the function redir_pipe,
 * which returns 0 for any pipe that isn't the last and 0 or
 * error code if the pipe is the last.
*/
static int	handle_pipeline(t_prompt prompt)
{
	t_list	*command_cpy;
	int		tmp_fd[2];
	int		exit_status;

	tmp_fd[0] = dup(STDIN_FILENO);
	if (tmp_fd[0] == -1)
		terminate(ERR_DUP, 1);
	tmp_fd[1] = dup(STDOUT_FILENO);
	if (tmp_fd[1] == -1)
		terminate(ERR_DUP, 1);
	command_cpy = prompt.cmd_line;
	while (command_cpy)
	{
		exit_status = redir_pipe(command_cpy, prompt, tmp_fd);
		command_cpy = command_cpy->next;
	}
	if (close(tmp_fd[0]) != 0)
		terminate(ERR_CLOSE, 1);
	if (close(tmp_fd[1]) != 0)
		terminate(ERR_CLOSE, 1);
	return (exit_status);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_prompt	prompt;

	if (argc != 1)
		terminate(ERR_ARGS, 0);
	init_shell();
	init_prompt(&prompt, argv, envp);
	while (1)
	{
		set_sigint_action();
		do_sigign(SIGQUIT);
		prompt.exit_status = handle_input(&prompt);
		if (prompt.exit_status == -1)
			break ;
		if (prompt.exit_status == 0)
			prompt.exit_status = handle_pipeline(prompt);
		if (prompt.cmd_line != NULL)
			free_cmd_line(&prompt.cmd_line);
	}
	free_environ(&prompt.environ);
	return (prompt.exit_status);
}
