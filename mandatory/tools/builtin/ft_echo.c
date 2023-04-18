/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:46:21 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/18 17:20:43 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_builtins.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

static void	print_arguments(int ac, char **av, t_bool flag);
static int	check_only_n(char *str);

int	ft_echo(int ac, char **av)
{
	t_bool	flag;

	flag = TRUE;
	if (ac > 1)
	{
		if (check_only_n(av[1]))
		{
			if (!ft_strncmp(av[1], MS_FLGCMP, ft_strlen(MS_FLGCMP)))
				flag = FALSE;
		}
		print_arguments(ac - 1, &av[1], flag);
	}
	if (flag == TRUE)
		printf("\n");
	return (EXIT_SUCCESS);
}

static void	print_arguments(int ac, char **av, t_bool flag)
{
	ssize_t	idx;

	idx = 0;
	while (idx < ac)
	{
		if (flag == FALSE)
		{
			if (!ft_strncmp(av[idx], MS_FLGCMP, ft_strlen(MS_FLGCMP)))
			{
				flag = FALSE;
				idx++;
			}
			else
				flag = TRUE;
			continue ;
		}
		else
		{
			printf("%s", av[idx]);
			if (idx + 1 != ac)
				printf(" ");
		}
		idx++;
	}
}

static int	check_only_n(char *str)
{
	ssize_t	idx;

	idx = 0;
	if (str[idx] == '-')
		idx++;
	while (str[idx] == 'n')
		idx++;
	return (str[idx] == '\0');
}
