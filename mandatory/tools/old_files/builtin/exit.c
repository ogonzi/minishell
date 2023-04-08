/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:16:24 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/05 01:21:21 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_fd.h"

#include <stdio.h>
#include <stdlib.h>

#define ERRCODE0	(int)0
#define ERRCODE1	(int)1

#define ERRMSG0	(char *)"bash: exit: too many arguments\n"
#define ERRMSG1	(char *)"numeric argument required\n"

static int	ft_while_isdigit(char *str);
static int	error_exit(int err, char *str);

int	main(int ac, char **av)
{
	t_ll	nbr;

	printf("exit\n");
	if (ac == 1)
		return (0);
	if (ac > 1 && !ft_while_isdigit(av[1]))
		return (error_exit(ERRCODE1, av[1]));
	if (ac > 2)
		return (error_exit(ERRCODE0, NULL));
	nbr = ft_atoll_base(av[1], STR_BASE10);
	printf("%lld\n", nbr);
	if (ft_strncmp(av[1], ft_lltoa_base(nbr, STR_BASE10), ft_strlen(av[1])))
		return (error_exit(ERRCODE1, av[1]));
	return ((unsigned char)nbr);
}

static int	error_exit(int err, char *str)
{
	if (err == ERRCODE0)
	{
		ft_printf_fd(STDERR_FILENO, "%s", ERRMSG0);
		return (1);
	}
	if (err == ERRCODE1)
	{
		ft_printf_fd(STDERR_FILENO, "bash: exit: %s: %s", str, ERRMSG1);
		return (255);
	}
	return (1);
}

static int	ft_while_isdigit(char *str)
{
	if (ft_issign(*str))
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}