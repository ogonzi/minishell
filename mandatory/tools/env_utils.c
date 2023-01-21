/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:54:04 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/01/21 02:41:49 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	count_env(char **ev)
{
	int	idx;

	idx = 0;
	while (ev[idx])
		idx++;
	return (idx);
}

char	**copy_env(char **cpy, char **ev, int count)
{
	ssize_t	idx;

	idx = -1;
	while (++idx < count)
	{
		cpy[idx] = (char *)malloc(sizeof(char) + ft_strlen(ev[idx]) + 1);
		if (!cpy)
		{
			ft_printf_fd(STDERR_FILENO, "Something went wrong...\n\a");
			return (NULL);
		}
		cpy[idx] = ev[idx];
	}
	return (cpy);
}
