/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:51:36 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/13 16:48:32 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

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

static int	handle_input(t_prompt *prompt)
{
	char	*buf;
	int		len_buf;
	int		err;

	buf = readline("msh> ");
	if (buf == NULL)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		return (-1);
	}
	len_buf = ft_strlen(buf);
	if (len_buf != 0)
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

static void	init_prompt(t_prompt *prompt, char *argv[], char *envp[])
{
	prompt->cmd_line = NULL;
	prompt->environ = NULL;
	prompt->exit_status = 0;
	custom_getpid(prompt);
	set_environ(prompt, envp);
	init_env_vars(prompt, argv);
}

static void	redir_pipe(t_list *command_cpy, t_prompt prompt, int *tmp_fd)
{
	pid_t	pid;
	int		fd[2];

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (command_cpy->next)
	{
		pipe(fd);
		pid = fork();
		if (pid)
		{
			close(fd[1]);
			close(*tmp_fd);
			*tmp_fd = fd[0];
		}
		else if (!pid)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			char *argv[] = {"echo", "hello", NULL};
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			dup2(*tmp_fd, STDIN_FILENO);
			close(*tmp_fd);
			execve("/bin/echo", argv, 0);
			write(STDERR_FILENO, "Error\n", 6);
		}
	}
	else {
		pid = fork();
		if (pid) {
			close(*tmp_fd);
			while (waitpid(-1, NULL, WUNTRACED) != -1)
				;
			*tmp_fd = dup(STDIN_FILENO);
		}
		else if (!pid) {
			char *argv[] = {"wc", NULL, NULL};
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			dup2(*tmp_fd, STDIN_FILENO);
			close(*tmp_fd);
			execve("/bin/wc", argv, 0);
			write(STDERR_FILENO, "Error\n", 6);
		}
	}
	(void)prompt;
}

static void handle_pipeline(t_prompt prompt)
{
	t_list	*command_cpy;
	int		tmp_fd;

	tmp_fd = dup(STDIN_FILENO);
	command_cpy = prompt.cmd_line;
	while (command_cpy)
	{
		redir_pipe(command_cpy, prompt, &tmp_fd);
		command_cpy = command_cpy->next;
	}
	close(tmp_fd);
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
		handle_pipeline(prompt);
		print_list(prompt.cmd_line);
		if (prompt.cmd_line != NULL)
			free_all(&prompt);
	}
	return (prompt.exit_status);
}
