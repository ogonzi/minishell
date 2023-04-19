/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:53:40 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/19 20:18:35 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

static void	handle_sig(int sig);

void	set_sigint_action_heredoc(void)
{
	struct sigaction	signal;

	signal.sa_handler = &handle_sig;
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	if (sigaction(SIGINT, &signal, NULL) < 0)
		terminate(ERR_SIG, EXIT_FAILURE);
}

static void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf_fd(STDOUT_FILENO, "\n");
		exit(TERMINATE_CTRL_C);
	}
}
