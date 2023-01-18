/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:50:38 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/01/18 16:33:02 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_fd.h"

#include <stdio.h>

#define PWDCMP	(char *)"PWD="

int	main(int ac, char **av, char **ev)
{
	ssize_t	idx;
	ssize_t	count;

	idx = -1;
	count = ft_strlen(PWDCMP);
	UNUSED(av);
	if (ac > 1)
	{
		ft_printf_fd(STDERR_FILENO, "pwd: too many arguments\a\n");
		return (1);
	}
	while (ev[++idx])
	{
		if (!ft_strncmp(ev[idx], PWDCMP, count))
		{
			while (count--)
				ev[idx]++;
			printf("%s\n", ev[idx]);
			return (0);
		}
	}
	return (1);
}
