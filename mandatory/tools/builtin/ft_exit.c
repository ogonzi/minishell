/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:54:03 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/25 15:49:46 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_builtins.h"
#include "mnshll_error.h"

extern int	g_exit_status;

#define ERRCODE0	(int)0
#define ERRCODE1	(int)1

#define ERRMSG0	(char *)"too many arguments\n"
#define ERRMSG1	(char *)"numeric argument required\n"

static void	error_exit(int err, char *str);

void	ft_exit(int ac, char **av)
{
	t_ll	nbr;

	printf("exit\n");
	if (ac == 1)
		exit(g_exit_status);
	if (!av[1][0])
		error_exit(ERRCODE1, NULL);
	nbr = ft_atoll_base(av[1], STR_BASE10);
	if (ft_strncmp(av[1], ft_lltoa_base(nbr, STR_BASE10), ft_strlen(av[1])))
		error_exit(ERRCODE1, av[1]);
	if (ac > 2)
	{
		error_exit(ERRCODE0, NULL);
		g_exit_status = 1;
		return ;
	}
	exit((unsigned char)nbr);
}

static void	error_exit(int err, char *str)
{
	if (err == ERRCODE0)
	{
		ft_printf_fd(STDERR_FILENO, "msh: exit: %s", ERRMSG0);
		return ;
	}
	if (err == ERRCODE1)
	{
		ft_printf_fd(STDERR_FILENO, "msh: exit: %s: %s", str, ERRMSG1);
		exit(255);
	}
	exit(EXIT_FAILURE);
}
