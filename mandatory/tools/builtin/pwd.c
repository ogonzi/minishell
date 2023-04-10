/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:38:27 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/10 18:14:13 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_builtins.h"
#include "mnshll_error.h"

void	ft_pwd(size_t ac, char **ev)
{
	ssize_t	idx;
	ssize_t	count;

	idx = -1;
	count = ft_strlen(MS_PWDCMP);
	if (ac > 1)
		terminate(ERR_PWD, EXIT_FAILURE);
	while (ev[++idx])
	{
		if (!ft_strncmp(ev[idx], MS_PWDCMP, count))
		{
			while (count--)
				ev[idx]++;
			printf("%s\n", ev[idx]);
			exit(EXIT_SUCCESS);
		}
	}
	exit(EXIT_FAILURE);
}
