/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:31:21 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/11 13:11:54 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_builtins.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

static int	print_declare_env(char **ev, ssize_t size, t_prompt *prompt);
static void	bubble_sort(char **arr, int len);

int	ft_export(int ac, char **av, char **ev, t_prompt *prompt)
{
	UNUSED(av);
	if (ac == 1)
		return (print_declare_env(ev, ft_strcount(ev), prompt));
	return (0);
}

static int	print_declare_env(char **ev, ssize_t size, t_prompt *prompt)
{
	char	**cpy_env;
	ssize_t	idx;

	cpy_env = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!cpy_env)
		ft_prompt_clear(prompt, ERR_MEM, 1);
	idx = -1;
	while (ev[++idx])
	{
		cpy_env[idx] = ft_strdup(ev[idx]);
		if (!cpy_env)
			ft_prompt_clear(prompt, ERR_MEM, 1);
	}
	bubble_sort(cpy_env, size);
	idx = -1;
	while (++idx < size)
		printf("declare -x %s\n", cpy_env[idx]);
	ft_memfree(cpy_env);
	return (EXIT_SUCCESS);
}

static void	bubble_sort(char **arr, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
