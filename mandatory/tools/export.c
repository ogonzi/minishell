/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:35:53 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/01/21 03:04:33 by cpeset-c         ###   ########.fr       */
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
	// cpy = sort_env(cpy); To implement sort
	while (++idx < count)
		printf("declare -x %s\n", cpy[idx]);
	ft_memfree(cpy, idx);
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
