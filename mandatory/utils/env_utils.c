/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:18:49 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/07 19:53:05 by cpeset-c         ###   ########.fr       */
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
