/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:33:07 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/09 18:48:24 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <term.h>
#include <unistd.h>
#include "utils.h"
#include "ft_printf.h"

/*
 * printf is not safe to use inside sig handlers
 */

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signals(void)
{
	struct sigaction	sa;
	struct sigaction	sa_ign;

	sa.sa_handler = &handle_sig;
	sa_ign.sa_handler = SIG_IGN;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		terminate(ERR_SIG, 1);
	if (sigaction(SIGQUIT, &sa_ign, NULL) == -1)
		terminate(ERR_SIG, 1);
}
