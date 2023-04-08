/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words_env_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 19:57:15 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/08 11:48:04 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

int	get_env_var_length(char *word, ssize_t *idx, t_env *env)
{
	t_unt	start;
	char	*env_var;
	int		length_env_var;
	char	*expanded_env_var;

	start = *idx;
	while (ft_isalnum(word[*idx]) || word[*idx] == '_')
		(*idx)++;
	env_var = ft_substr(word, start, *idx - start);
	if (!env_var)
		exit(1); //	terminate(ERR_MEM, 1);
	expanded_env_var = ((t_env *)ft_env_iter(env, env_var))->env_data;
	length_env_var = ft_strlen(expanded_env_var);
	ft_delete(env_var);
	return (length_env_var);
}

void	set_new_word(char *word, char *cpy_word, int exit_status, t_env *env)
{
	int		i;
	int		j;
	int		k;
	char	*expanded_env_var;

	i = 0;
	j = 0;
	while (cpy_word[i])
	{
		if (cpy_word[i] == '$'
			&& (ft_isalnum(cpy_word[i + 1]) || cpy_word[i + 1] == '_'))
		{
			i++;
			expanded_env_var = get_env_var(cpy_word, &i, env);
			k = 0;
			while (expanded_env_var[k] != '\0')
				copy_char_to_word(word, expanded_env_var, &k, &j);
		}
		else if (cpy_word[i] == '$' && cpy_word[i + 1] == '?')
			set_exit_status_to_word(word, exit_status, &i, &j);
		else
			copy_char_to_word(word, cpy_word, &i, &j);
	}
}

char	*get_env_var(char *word, int *idx, t_env *env)
{
	int		start;
	char	*env_var;
	char	*expanded_env_var;

	start = *idx;
	while (ft_isalnum(word[*idx]) || word[*idx] == '_')
		(*idx)++;
	env_var = ft_substr(word, start, *idx - start);
	if (!env_var)
		exit(1); //	terminate(ERR_MEM, 1);
	expanded_env_var = ((t_env *)ft_env_iter(env, env_var))->env_data;
	ft_delete(env_var);
	return (expanded_env_var);
}
