/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:46:21 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/19 12:32:58 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_builtins.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

static void	print_arguments(int ac, char **av, t_bool flag);
static void	aux_print_args(char *str, int idx, int ac);

int	ft_echo(int ac, char **av)
{
	t_bool	flag;
	int		i;
	int		j;

	flag = TRUE;
	i = 1;
	while (i < ac && av[i][0] == '-'
		&& !ft_strncmp(av[i], MS_FLGCMP, strlen(MS_FLGCMP)))
	{
		j = 1;
		while (av[i][j] == 'n')
			j++;
		if (av[i][j] == '\0')
		{
			flag = FALSE;
			i++;
		}
		else
			break ;
	}
	print_arguments(ac - i, &av[i], flag);
	if (flag == TRUE)
		printf("\n");
	return (EXIT_SUCCESS);
}

static void	print_arguments(int ac, char **av, t_bool flag)
{
	ssize_t	idx;

	idx = -1;
	while (++idx < ac)
	{
		if (flag == FALSE)
			aux_print_args(av[idx], idx, ac);
		else
		{
			if (!ft_strncmp(av[idx], MS_FLGCMP, ft_strlen(MS_FLGCMP)))
			{
				flag = FALSE;
				idx++;
			}
			else
				aux_print_args(av[idx], idx, ac);
		}
	}
}

static void	aux_print_args(char *str, int idx, int ac)
{
	printf("%s", str);
	if (idx + 1 != ac)
		printf(" ");
}

