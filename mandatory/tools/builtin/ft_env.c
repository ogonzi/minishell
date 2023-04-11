/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:20:03 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/11 12:59:59 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_builtins.h"
#include "mnshll_error.h"

static void	error_env(char *str);

int	ft_env(int ac, char **av, char **ev)
{
	ssize_t	idx;
	ssize_t	count;
	t_bool	flag;

	idx = -1;
	count = 0;
	flag = TRUE;
	if (ac > 1 && ft_strcmp(ft_strlowcase(av[1]), MS_ENVCMP))
		error_env(av[1]);
	if (ac > 2)
	{
		while (++count < ac)
		{
			if (ft_strcmp(ft_strlowcase(av[count]), MS_ENVCMP))
				flag = FALSE;
		}
	}
	if (flag == FALSE)
		error_env(av[count - 1]);
	while (ev[++idx])
		printf("%s\n", ev[idx]);
	return (EXIT_SUCCESS);
}

static void	error_env(char *str)
{
	ft_printf_fd(STDERR_FILENO, "env: %s: %s", str, ERR_ENV);
	exit(EXIT_FAILURE);
}
