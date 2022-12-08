/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:59:58 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/08 18:37:05 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <stdio.h>

void	handle_expand_env_var(char *word, int *i, int *remove_char)
{
	int		start;
	char	*env_var;

	(*i)++;
	start = *i;
	while (ft_isalnum(word[*i]) || word[*i] == '_')
		(*i)++;
	env_var = ft_substr((const char *)word, start, *i - start);
	if (env_var == NULL)
		terminate(ERR_MEM, 1);
	if (ft_strlen(env_var) > 0 && getenv(env_var) == NULL)
	{
		remove_char[start - 1] = 1;
		while (start < *i)
		{
			remove_char[start] = 1;
			start++;
		}
	}
	free(env_var);
}

void	expand(char *word, int *remove_char)
{
	int		i;
	int		single_quote_flag;
	int		is_double_quoted;

	i = 0;
	is_double_quoted = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '\"')
			set_opposite_binary(&is_double_quoted);
		if (word[i] == '\'' && is_double_quoted == 0)
			find_closing_quote(word, &i, &single_quote_flag, '\'');
		if (word[i] == '$' && (i == 0 || word[i - 1] != '\\'))
			handle_expand_env_var(word, &i, remove_char);
		else
			i++;
	}
}
