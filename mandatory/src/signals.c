/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:33:07 by ogonzale          #+#    #+#             */
/*   Updated: 2023/01/11 13:29:11 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <term.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "minishell_utils.h"
#include "ft_printf.h"

/*
 * printf is not safe to use inside sig handlers
 */

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	handle_child_sig(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(TERMINATE_CTRL_C);
	}
	if (signum == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit\n", 5);
		rl_on_new_line();
		exit(TERMINATE_QUIT);
	}
}

void	set_sigint_action(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sig;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		terminate(ERR_SIG, 1);
}

void	set_child_sigaction(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_child_sig;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, 0) == -1)
		terminate(ERR_SIG, 1);
	if (sigaction(SIGQUIT, &sa, 0) == -1)
		terminate(ERR_SIG, 1);
}

void	do_sigign(int signum)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(signum, &sa, NULL) == -1)
		terminate(ERR_SIG, 1);
}