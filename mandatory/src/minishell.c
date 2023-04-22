/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:38:30 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/22 11:33:11 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_parser.h"
#include "mnshll_words.h"
#include "mnshll_expand.h"
#include "mnshll_exec.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

int	g_exit_status = 0;

static int	handler_input(t_prompt *prompt);
static int	handler_pipeline(t_prompt *prompt);

int	main(int ac, char **av, char **ev)
{
	t_prompt	prompt;

	if (ac != 1)
		terminate(ERR_ARGS, EXIT_FAILURE);
	init_prompt(&prompt, av, ev);
	while (TRUE)
	{
		set_sigint_action();
		do_sigign(SIGQUIT);
		g_exit_status = handler_input(&prompt);
		if (g_exit_status == -2)
			break ;
		if (g_exit_status == 0)
			g_exit_status = handler_pipeline(&prompt);
		if (g_exit_status == 42)
			g_exit_status = 0;
		if (prompt.cmdline)
			ft_cmdline_clear(&prompt.cmdline, (void *)ft_delete);
	}
	ft_env_clear(&prompt.env, (void *)ft_delete);
	ft_env_clear(&prompt.export, (void *)ft_delete);
	return (0);
}

void	init_prompt(t_prompt *prompt, char **av, char **ev)
{
	read_banner();
	prompt->cmdline = NULL;
	prompt->env = NULL;
	prompt->error_status = 0;
	custom_getpid(prompt);
	if (!(*ev))
	{
		custom_void_env(&prompt->env, av[0]);
		custom_void_env(&prompt->export, av[0]);
	}
	else
	{
		set_environ(&prompt->env, ev);
		set_environ(&prompt->export, ev);
		set_custom_env(&prompt->env, av[0]);
		set_custom_env(&prompt->export, av[0]);
	}
}

static t_bool	str_all_space(char *buf)
{
	int	i;
	int	buf_len;

	buf_len = ft_strlen(buf);
	i = -1;
	while (++i < buf_len)
	{
		if (!ft_isspace(buf[i]))
			return (FALSE);
	}
	return (TRUE);
}

static int	handler_input(t_prompt *prompt)
/*
 * If the user enters nothing, readline returns NULL, and the function prints
 * "exit" to STDOUT_FILENO and returns -1, indicating that the program should
 * exit.

 * If the user enters a command, the function adds it to the command history 
 * using add_history.

 * The function then calls split_cmd_line to split the command into individual
 * commands and pipes, and sets the prompt->error_status flag accordingly.

 * If prompt->error_status is FALSE, the function calls split_words to split the
 * individual commands into words, and sets prompt->error_status accordingly.

 * Finally, the function calls expand_words to expand any environment variables
 * or special characters in the command, and returns 0 if all of the above steps
 * were successful.
*/
{
	char	*buf;

	buf = readline("msh> ");
	if (!buf)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		return (-2);
	}
	if (ft_strlen(buf) != 0 && str_all_space(buf) == FALSE)
	{
		add_history(buf);
		prompt->error_status = split_cmd_line(prompt, buf);
		if (prompt->error_status != FALSE)
			return (258);
		prompt->error_status = split_words(prompt);
		if (prompt->error_status != FALSE)
			return (258);
		expand_words(prompt);
	}
	else
	{
		ft_delete(buf);
		return (42);
	}
	ft_delete(buf);
	return (0);
}

static int	handler_pipeline(t_prompt *prompt)
/*
 * Here's a breakdown of the handler_pipeline() function:

	* It first makes a copy of the prompt's command line.

	* It sets up two file descriptors to temporarily store the standard input and
	* output (which are later restored).
	
	* It then iterates through each command in the pipeline and sets up redirection
	* for input/output using the redir_pipe() function. The tmp_fd array is passed
	* to this function and is updated with the file descriptors of the new
	* input/output streams.

	* Finally, it restores the standard input and output file descriptors to their
	* original values and returns the exit status.

 * The redir_pipe() function is responsible for setting up the pipes between the 
 * commands and redirecting input/output. The tmp_fd array is used to store the
 * file descriptors of the pipes. The function then forks a child process to
 * execute the command and handles the redirection in the child process.
 * It returns the exit status of the command.
*/
{
	t_list	*command_cpy;
	int		tmp_fd[2];
	int		exit_status;
	int		is_first;

	tmp_fd[0] = dup(STDIN_FILENO);
	if (tmp_fd[0] == ERRNUM)
		ft_prompt_clear(prompt, ERR_DUP, EXIT_FAILURE);
	tmp_fd[1] = dup(STDOUT_FILENO);
	if (tmp_fd[1] == ERRNUM)
		ft_prompt_clear(prompt, ERR_DUP, EXIT_FAILURE);
	command_cpy = prompt->cmdline;
	is_first = TRUE;
	while (command_cpy)
	{
		exit_status = redir_pipe(command_cpy, prompt, tmp_fd, is_first);
		command_cpy = command_cpy->next;
		is_first = FALSE;
	}
	if (close(tmp_fd[0]))
		ft_prompt_clear(prompt, ERR_CLOSE, EXIT_FAILURE);
	if (close(tmp_fd[1]))
		ft_prompt_clear(prompt, ERR_CLOSE, EXIT_FAILURE);
	return (exit_status);
}
