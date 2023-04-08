/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mnshll_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:10:27 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/08 18:07:17 by cpeset-c         ###   ########.fr       */
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
	return (env);
}
