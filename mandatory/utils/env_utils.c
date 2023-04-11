/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:18:49 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/11 18:34:34 by cpeset-c         ###   ########.fr       */
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

char	**ft_split_once(char const *s, char c)
{
	size_t	i;
	char	**result;

	result = (char **)ft_calloc(3, sizeof(char *));
	if (!result || !s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	result[0] = ft_substr(s, 0, i);
	if (!result[0])
		return (ft_delete(result[0]));
	if (!s[i])
		result[1] = NULL;
	else
	{
		result[1] = ft_substr(s, i + 1, ft_strlen(s + i + 1));
		if (!result[1])
		{
			ft_delete(result[0]);
			return (ft_delete(result));
		}
	}
	return (result);
}

char	*ft_strtrim_charset_end(char *str, char *end)
{
	size_t	str_len;
	size_t	end_len;

	if (!str || !end)
		return (NULL);
	str_len = ft_strlen(str);
	end_len = ft_strlen(end);
	if (end_len > str_len)
		return (NULL);
	if (ft_strcmp(str + str_len - end_len, end) == 0)
	{
		str[str_len - end_len] = '\0';
		return (str);
	}
	return (ft_strdup(str));
}
