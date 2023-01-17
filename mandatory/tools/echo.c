/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:14:18 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/01/17 19:05:39 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_fd.h"

#include <stdio.h>

#define FLGCMP	(char *)"-n"

static void	print_arguments(int ac, char **av, t_bool flag);
static int	check_only_n(char *str);

int	main(int ac, char **av)
{
	t_bool	flag;

	flag = TRUE;
	if (ac > 1)
	{
		if (check_only_n(av[1]))
		{
			if (!ft_strncmp(av[1], FLGCMP, ft_strlen(FLGCMP)))
				flag = FALSE;
		}
		print_arguments(ac - 1, &av[1], flag);
	}
	if (flag == TRUE)
		printf("\n");
	return (0);
}

static void	print_arguments(int ac, char **av, t_bool flag)
{
	ssize_t	idx;

	idx = 0;
	while (idx < ac)
	{
		if (flag == FALSE)
		{
			idx++;
			flag = TRUE;
			continue ;
		}
		printf("%s", av[idx]);
		idx++;
		if (idx != ac)
			printf(" ");
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
	if (str[idx])
		return (FALSE);
	return (TRUE);
}
