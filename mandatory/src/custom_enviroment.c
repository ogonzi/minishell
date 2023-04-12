/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_enviroment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:50:15 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/12 16:08:02 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_builtins.h"
#include "mnshll_error.h"

static t_env	*ft_custom_env_node(char *var, char *data);

void	custom_void_env(t_env **env, char *prog)
{
	ssize_t	idx;

	idx = 4;
	while (--idx)
	{
		if (idx == 3)
			*env = ft_custom_env_node("PWD", get_custom_pwd());
		else if (idx == 2)
			(*env)->next = ft_custom_env_node("SHLVL", "1");
		else if (idx == 1)
			(*env)->next->next = ft_custom_env_node("_",
					ft_strtrim(prog, "."));
	}
}

static t_env	*ft_custom_env_node(char *var, char *data)
{
	static t_unt	idx = 0;
	t_env			*node;

	node = malloc(sizeof(t_env));
	if (!node)
		terminate(ERR_MEM, EXIT_FAILURE);
	node->env_var = var;
	node->env_data = data;
	node->idx = ++idx;
	node->next = NULL;
	return (node);
}

char	*get_custom_pwd(void)
{
	char	*val;

	val = ft_calloc(MS_MAX_PATH, sizeof(char));
	if (!val)
		terminate(ERR_MEM, EXIT_FAILURE);
	if (getcwd(val, MS_MAX_PATH))
		return (val);
	return (NULL);
}
