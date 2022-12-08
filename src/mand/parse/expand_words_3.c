/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:38:07 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/08 16:03:51 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

char	*get_env_var(char *word, int *i)
{
	int		start;
	char	*env_var;
	char	*expanded_env_var;

	start = *i;
	while (ft_isalnum(word[*i]) || word[*i] == '_')
		(*i)++;
	env_var = ft_substr(word, start, *i - start);
	if (env_var == NULL)
		terminate(ERR_MEM, 1);
	expanded_env_var = getenv(env_var);
	free(env_var);
	return (expanded_env_var);
}

void	set_exit_status_to_word(char *word, int exit_status, int *i, int *j)
{
	char	*exit_status_str;
	int		k;

	*i += 2;
	exit_status_str = ft_itoa(exit_status);
	k = 0;
	while (exit_status_str[k] != '\0')
		copy_char_to_word(word, exit_status_str, &k, j);
	free(exit_status_str);
}

void	set_new_word(char *word, char *cpy_word, int exit_status)
{
	int		i;
	int		j;
	int		k;
	char	*expanded_env_var;

	i = 0;
	j = 0;
	while (cpy_word[i] != '\0')
	{
		if (cpy_word[i] == '$'
			&& (ft_isalnum(cpy_word[i + 1]) || cpy_word[i + 1] == '_'))
		{
			i++;
			expanded_env_var = get_env_var(cpy_word, &i);
			k = 0;
			while (expanded_env_var[k] != '\0')
				copy_char_to_word(word, expanded_env_var, &k, &j);
		}
		else if (cpy_word[i] == '$' && cpy_word[i + 1] == '?')
			set_exit_status_to_word(word, exit_status, &i, &j);
		else
			copy_char_to_word(word, cpy_word, &i, &j);
	}
	word[j] = '\0';
}

char	*expand_env(char *word, int exit_status)
{
	int		old_length;
	int		new_length;
	char	*cpy_word;

	new_length = new_word_length(word, exit_status);
	old_length = ft_strlen(word);
	cpy_word = malloc(sizeof(char) * (old_length + 1));
	if (cpy_word == NULL)
		terminate(ERR_MEM, 1);
	ft_strlcpy(cpy_word, word, old_length + 1);
	free(word);
	word = NULL;
	word = malloc(sizeof(char) * (new_length + 1));
	set_new_word(word, cpy_word, exit_status);
	free(cpy_word);
	return (word);
}
