/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:36:51 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/01/21 03:04:48 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	unset_env(char **av, char **ev)
{
	char	**cpy;
	int		idx;

	idx = -1;
	cpy = (char **)malloc(sizeof(char *) * (count_env(ev) + 1));
	if (!cpy)
	{
		ft_printf_fd(STDERR_FILENO, "Something went wrong...\n\a");
		return ;
	}
	cpy[count_env(ev)] = NULL;
	cpy = copy_env(cpy, ev, count_env(ev));
	while (*av)
	{
		while (cpy[++idx])
		{
			if (!ft_strncmp(*av, cpy[idx], ft_strlen(*av))
				&& cpy[idx][ft_strlen(*av + 1) + 1] == '=')
			{
				// Here goes the delete function instead of printf
				// Will have to redo de char **cpy with mallocs
				printf("%zu - %s -> %c\n", ft_strlen(*av), cpy[idx], cpy[idx][ft_strlen(*av + 1) + 1]);
				return ;
			}
		}
		av++;
	}
}

// -=-=-=-=-=-=-
// Mains are unnecesary

int	main(int ac, char **av, char **ev)
{
	UNUSED(ac);
	if (ac == 1)
		return (1);
	unset_env(&av[1], ev);
	return (0);
}
