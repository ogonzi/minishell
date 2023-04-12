/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:06:40 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/12 18:39:14 by cpeset-c         ###   ########.fr       */
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

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		terminate(ERR_MEM, 1);
	new->env_var = ft_strdup("OLDPWD");
	new->env_data = ft_strdup(get_custom_pwd());
	new->next = NULL;
	env->next = new;
}

void	export_pwd(t_env *env)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		terminate(ERR_MEM, 1);
	new->env_var = ft_strdup("PWD");
	new->env_data = ft_strdup(get_custom_pwd());
	new->next = NULL;
	env->next = new;
}

void	before_export_pwd(t_prompt **prompt)
{
	export_pwd(ft_env_last(&(*prompt)->env));
	export_pwd(ft_env_last(&(*prompt)->export));
}

void	before_export_oldpwd(t_prompt **prompt)
{
	export_oldpwd(ft_env_last(&(*prompt)->env));
	export_oldpwd(ft_env_last(&(*prompt)->export));
}
