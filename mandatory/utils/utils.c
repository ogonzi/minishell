/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:53:26 by ogonzale          #+#    #+#             */
/*   Updated: 2023/01/23 18:33:19 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_utils.h"

void	terminate(char *s, int syserr)
{
	if (syserr == TRUE)
		ft_printf_fd(STDERR_FILENO, "%s", s);
	else
		ft_printf_fd(STDERR_FILENO, "%s", s);
	exit(EXIT_FAILURE);
}

int	free_and_return_error_code(char **str, int err)
{
	free(*str);
	*str = NULL;
	return (err);
}
