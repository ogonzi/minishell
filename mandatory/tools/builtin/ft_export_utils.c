/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:17:43 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/17 20:07:24 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_builtins.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

void	before_export(t_env **env, char *data, t_bool flag)
{
	char	**str;
	t_env	*new_node;

	str = ft_split_once(data, '=');
	if (!str)
		terminate(ERR_MEM, 1);
	new_node = ft_env_iter(*env, str[0]);
	if (new_node)
	{
		ft_delete(new_node->env_data);
		if (flag)
			new_node->env_data = check_string(str[1]);
		else
			new_node->env_data = check_string("");
		return ;
	}
	else
		mns_export(env, flag, str);
}

void	mns_export(t_env **env, t_bool flag, char **str)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		terminate(ERR_MEM, 1);
	new_node->env_var = check_string(str[0]);
	if (flag)
		new_node->env_data = check_string(str[1]);
	else
		new_node->env_data = check_string("");
	new_node->idx = 0;
	new_node->next = NULL;
	ft_env_addback(env, new_node);
	ft_memfree(str);
}

void	bubble_sort(char **arr, int size)
{
	int		i;
	int		j;
	char	*tmp;

	if (size < 0)
		return ;
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
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

char	*aux_print_declare_env_join(t_env *cpy)
{
	char	*str1;
	char	*str2;
	char	*str3;
	char	*str4;

	str1 = ft_strjoin(cpy->env_data, "\"");
	if (!str1)
		terminate(ERR_MEM, EXIT_FAILURE);
	str2 = ft_strjoin("\"", str1);
	if (!str2)
		terminate(ERR_MEM, EXIT_FAILURE);
	ft_delete(str1);
	str3 = ft_strjoin("=", str2);
	if (!str3)
		terminate(ERR_MEM, EXIT_FAILURE);
	ft_delete(str2);
	str4 = ft_strjoin(cpy->env_var, str3);
	if (!str4)
		terminate(ERR_MEM, EXIT_FAILURE);
	ft_delete(str3);
	return (str4);
}
