/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:47:46 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/01/16 14:34:29 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_fd.h"
#include <stdio.h>
#include <stdlib.h>

#define ERRMSG	(char *)"No such file or directory\n"
#define ENVCMP	(char *)"env"

int	error_env(char *str);

int	main(int ac, char **av, char **ev)
{
	ssize_t	idx;
	t_bool	flag;
	ssize_t	count;

	idx = -1;
	flag = TRUE;
	count = 0;
	if (ac > 1 && ft_strcmp(ft_strlowcase(av[1]), ENVCMP))
		return (error_env(av[1]));
	if (ac > 2)
	{
		while (++count < ac)
		{
			if (ft_strcmp(ft_strlowcase(av[count]), ENVCMP))
				flag = FALSE;
		}
	}
	if (flag == FALSE)
		return (error_env(av[count - 1]));
	while (ev[++idx])
		printf("%s\n", ev[idx]);
	return (0);
}

int	error_env(char *str)
{
	ft_printf_fd(STDERR_FILENO, "env: %s: %s", str, ERRMSG);
	return (1);
}
