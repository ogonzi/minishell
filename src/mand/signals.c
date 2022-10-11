/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:33:07 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/11 18:00:44 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <term.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include "utils.h"
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

void	handle_child_sig(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(130);
	}
	if (signum == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit\n", 5);
		rl_on_new_line();
		exit(131);
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
	if (sigaction(signum, &sa, NULL) == -1)
		terminate(ERR_SIG, 1);
}
