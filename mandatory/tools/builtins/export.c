/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:35:53 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/02 18:01:18 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_declare_env(char **ev);

char	**export_handler(int ac, char **av, char **ev)
{
	UNUSED(av);
	if (ac == 1)
		print_declare_env(ev);
	return (NULL);
}

static size_t	ft_dimlen(char **arr)
{
	size_t	idx;

	idx = 0;
	while (arr[idx])
		++idx;
	return (idx);
}

static void	sort_env(char **cpy)
{
	char	*temp;
	int		i;
	int		j;
	int		n;

	i = 0;
	j = 0;
	n = ft_dimlen(cpy) - 1;
	while (++i < n)
	{
		while (++j < n - i + 1)
		{
			if (ft_strcmp(cpy[j], cpy[j + 1]) > 0)
			{
				temp = cpy[j];
				cpy[j] = cpy[j + 1];
				cpy[j + 1] = temp;
			}
		}
	}
}

static void	print_declare_env(char **ev)
{
	char	**cpy;
	int		count;
	int		idx;

	count = count_env(ev);
	idx = -1;
	cpy = (char **)malloc(sizeof(char *) * (count + 1));
	if (!cpy)
	{
		ft_printf_fd(STDERR_FILENO, "Something went wrong...\n\a");
		return ;
	}
	cpy[count] = NULL;
	cpy = copy_env(cpy, ev, count);
	sort_env(cpy);
	while (++idx < count)
		printf("declare -x %s\n", cpy[idx]);
	ft_memfree(cpy);
}

// -=-=-=-=-=-=-=-
// Mains are unnecesary

int	main(int ac, char **av, char **ev)
{
	UNUSED(av);
	if (ac == 1)
		export_handler(1, NULL, ev);
	return (0);
}
