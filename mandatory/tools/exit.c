/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:16:24 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/01/15 20:57:37 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_fd.h"

#include <stdio.h>
#include <stdlib.h>

#define ERRMSG0	(char *)"bash: exit: too many arguments\n"
#define ERRMSG1	(char *)": numeric argument required\n"

int	ft_while_isdigit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (TRUE);
		str++;
	}
	return (FALSE);
}

int	main(int ac, char **av)
{
	t_ll	limit;

	printf("exit\n");
	printf("%ld\n", -922337203685477580);
	exit(0);
	if (ac > 2)
	{
		ft_printf_fd(STDERR_FILENO, "%s", ERRMSG0);
		exit(255);
	}
	limit = ft_atoll_base(av[1], STR_BASE10);
	// if ()
	// {

	// }
	return (1);
}