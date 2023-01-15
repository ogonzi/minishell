/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:47:46 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/01/15 20:52:00 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_fd.h"
#include <stdio.h>
#include <stdlib.h>

#define ERRMSG	(char *)"No such file or directory\n"
#define ENVCMP	(char *)"env"

int	main(int ac, char **av, char **ev)
{
	ssize_t	idx;

	idx = -1;
	if (ac > 1 && ft_strcmp(ft_strlowcase(av[1]), ENVCMP))
	{
		ft_printf_fd(STDERR_FILENO, "env: %s: %s", av[1], ERRMSG);
		return (1);
	}
	else if (ac > 1 && !ft_strcmp(ft_strlowcase(av[1]), ENVCMP))
	{
		while (ev[++idx])
			printf("%s\n", ev[idx]);
		return (0);
	}
	else
	{
		while (ev[++idx])
			printf("%s\n", ev[idx]);
		return (0);
	}
	return (1);
}
