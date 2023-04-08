/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:45:33 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/03/21 13:12:36 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_error.h"

void	terminate(char *s, int syserr)
{
	if (syserr == TRUE)
		ft_printf_fd(STDERR_FILENO, "%s", s);
	else
		ft_printf_fd(STDERR_FILENO, "%s", s);
	exit(EXIT_FAILURE);
}
