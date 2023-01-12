/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:47:46 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/01/12 21:31:36 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"
#include <stdio.h>
#include <stdlib.h>

#define ERRMSG	(char *)"No such file or directory"

int	main(int ac, char **av, char **ev)
{
	ssize_t	idx;

	if (ac > 1)
	{
		ft_printf_fd(STDERR_FILENO, "env: %s:%s", av[2], ERRMSG);
		return (1);
	}
	idx = -1;
	while (ev[++idx])
		printf("%s\n", ev[idx]);
	return (0);
}
