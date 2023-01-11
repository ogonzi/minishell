/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:12:05 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/01/11 13:29:11 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_utils.h"

void	copy_char_to_word(char *word, char *cpy_word,
		int *from_index, int *to_index)
{
	word[*to_index] = cpy_word[*from_index];
	(*from_index)++;
	(*to_index)++;
}

int	get_env_var_length(char *word, int *i)
{
	int		start;
	char	*env_var;
	int		length_env_var;
	char	*expanded_env_var;

	start = *i;
	while (ft_isalnum(word[*i]) || word[*i] == '_')
		(*i)++;
	env_var = ft_substr(word, start, *i - start);
	if (env_var == NULL)
		terminate(ERR_MEM, 1);
	expanded_env_var = getenv(env_var);
	if (expanded_env_var == NULL)
		return (0);
	length_env_var = ft_strlen(expanded_env_var);
	free(env_var);
	return (length_env_var);
}

int	get_added_length(char *word, int *i, int *added_length, int exit_status)
{
	if (word[*i] == '$' && (ft_isalnum(word[*i + 1]) || word[*i + 1] == '_'))
	{
		(*i)++;
		*added_length += get_env_var_length(word, i);
		return (1);
	}
	if (word[*i] == '$' && word[*i + 1] == '?')
	{
		*added_length += ft_numsize(exit_status);
		*i += 2;
		return (1);
	}
	return (0);
}

int	new_word_length(char *word, int exit_status)
{
	int	i;
	int	base_length;
	int	added_length;

	i = 0;
	base_length = 0;
	added_length = 0;
	while (word[i] != '\0')
	{
		if (get_added_length(word, &i, &added_length, exit_status) == 0)
		{
			base_length++;
			i++;
		}
	}
	return (base_length + added_length);
}