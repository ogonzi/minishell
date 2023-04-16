/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:54:03 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/16 17:48:59 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_builtins.h"
#include "mnshll_error.h"

#define ERRCODE0	(int)0
#define ERRCODE1	(int)1

#define ERRMSG0	(char *)"bash: exit: too many arguments\n"
#define ERRMSG1	(char *)"numeric argument required\n"

// static int	ft_while_isdigit(char *str);
static void	error_exit(int err, char *str);

void	ft_exit(int ac, char **av)
{
	t_ll	nbr;

	printf("exit\n");
	if (ac == 1)
		exit(0);
	if (!av[1][0])
		error_exit(ERRCODE1, NULL);
	if (ac > 2)
		error_exit(ERRCODE0, NULL);
	nbr = ft_atoll_base(av[1], STR_BASE10);
	if (ft_strncmp(av[1], ft_lltoa_base(nbr, STR_BASE10), ft_strlen(av[1])))
		error_exit(ERRCODE1, av[1]);
	exit((unsigned char)nbr);
}

static void	error_exit(int err, char *str)
{
	if (err == ERRCODE0)
	{
		ft_printf_fd(STDERR_FILENO, "%s", ERRMSG0);
		exit(EXIT_FAILURE);
	}
	if (err == ERRCODE1)
	{
		ft_printf_fd(STDERR_FILENO, "mns: exit: %s: %s", str, ERRMSG1);
		exit(255);
	}
	exit(EXIT_FAILURE);
}
