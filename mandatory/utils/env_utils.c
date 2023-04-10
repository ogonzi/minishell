/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:18:49 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/10 10:44:07 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

void	custom_export(t_env *env, char *data)
{
	char	*aux;

	aux = ft_strdup(data);
	if (!aux)
		return ;
	ft_delete(env->env_data);
	env->env_data = aux;
}

t_env	*ft_env_iter(t_env *env, char *ref)
/*
 * This function is used to iterate over a linked list of environment variables
 * and find a specific one by its reference name. It takes two parameters: a pointer
 * to the head of the linked list env, and a string ref representing the name of
 * the environment variable to be found.
*/
{
	if (!env || !ref)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->env_var, ref))
			break ;
		env = env->next;
	}
	return (env);
}

size_t	ft_env_size(t_env *env)
{
	size_t	idx;
	t_env	*cpy;

	idx = 0;
	cpy = env;
	while (cpy)
	{
		cpy = cpy->next;
		++idx;
	}
	return (idx);
}

void	ft_env_clear(t_env **env, void (*del)(void *))
{
	t_env	*aux;

	if (!(*env))
		return ;
	while (*env)
	{
		aux = (*env)->next;
		del((*env)->env_data);
		del((*env)->env_var);
		del(*env);
		*env = aux;
	}
	*env = NULL;
}
