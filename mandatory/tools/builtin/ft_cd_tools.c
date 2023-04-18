/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:06:40 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/18 17:48:40 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_builtins.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

void	ft_swap_content(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	export_oldpwd(t_env *env)
{
	t_env	*new;
	char	*aux;

	aux = ft_strdup(get_custom_pwd());
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		terminate(ERR_MEM, 1);
	new->env_var = ft_strdup("OLDPWD");
	if (!new->env_var)
		terminate(ERR_MEM, EXIT_FAILURE);
	new->env_data = ft_strdup(aux);
	if (!new->env_data)
		terminate(ERR_MEM, EXIT_FAILURE);
	ft_delete(aux);
	new->next = NULL;
	env->next = new;
}

void	export_pwd(t_env *env)
{
	t_env	*new;
	char	*aux;

	aux = ft_strdup(get_custom_pwd());
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		terminate(ERR_MEM, 1);
	new->env_var = ft_strdup("PWD");
	if (!new->env_var)
		terminate(ERR_MEM, EXIT_FAILURE);
	new->env_data = ft_strdup(aux);
	if (!new->env_data)
		terminate(ERR_MEM, EXIT_FAILURE);
	ft_delete(aux);
	new->next = NULL;
	env->next = new;
}
