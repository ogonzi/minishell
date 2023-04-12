/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:21:48 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/12 19:01:40 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

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
	if (!env)
		return (NULL);
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
		if ((*env)->env_data)
			del((*env)->env_data);
		if ((*env)->env_var)
			del((*env)->env_var);
		del(*env);
		*env = aux;
	}
}

void	ft_env_addback(t_env **env, t_env *new)
{
	if (!*env)
	{
		*env = new;
		return ;
	}
	ft_env_last(env)->next = new;
}

t_env	*ft_env_last(t_env **env)
{
	t_env	*current;

	if (!env || !*env)
		return (NULL);
	current = *env;
	while (current->next)
		current = current->next;
	return (current);
}
