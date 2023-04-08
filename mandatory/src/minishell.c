/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:38:30 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/08 18:02:53 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

static int	handler_input(t_prompt *prompt);

int	main(int ac, char **av, char **ev)
{
	t_prompt	prompt;

	if (ac != 1)
		return (1);
		// terminate(ERR_ARGS, FALSE);
	init_prompt(&prompt, av, ev);
	while (TRUE)
	{
		set_sigint_action();
		do_sigign(SIGQUIT);
		prompt.exit_status = handler_input(&prompt);
		if (prompt.exit_status == ERROR_NUM)
			break ;
	}
	return (0);
}

void	init_prompt(t_prompt *prompt, char **av, char **ev)
{
	prompt->cmdline = NULL;
	prompt->env = NULL;
	prompt->error_status = 0;
	prompt->exit_status = 0;
	custom_getpid(prompt);
	if (!*ev)
		custom_void_env(prompt, av[0]);
	else
	{
		set_environ(prompt, ev);
		set_custom_env(prompt, av[0]);
	}
}

static int	handler_input(t_prompt *prompt)
/*
 * If the user enters nothing, readline returns NULL, and the function prints
 * "exit" to STDOUT_FILENO and returns -1, indicating that the program should exit.

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
		ft_printf_fd(STDOUT_FILENO, "exit\n");
		return (-1);
	}
	if (ft_strlen(buf) != 0)
	{
		add_history(buf);
		prompt->error_status = split_cmd_line(prompt, buf);
		if (prompt->error_status != FALSE)
			return (ERROR_NUM);
		prompt->error_status = split_words(prompt);
		if (prompt->error_status != FALSE)
			return (ERROR_NUM);
		expand_words(prompt);
	}
	ft_delete(buf);
	return (0);
}
