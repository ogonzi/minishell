/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:03:39 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/08 12:51:58 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

void	handle_expand_env_var(char *word, ssize_t *idx, int *remove_char)
{
	int		start;
	char	*env_var;

	(*idx)++;
	start = *idx;
	while (ft_isalnum (word[*idx]) || word[*idx] == '_')
		(*idx)++;
	env_var = ft_substr(word, start, *idx - start);
	if (!env_var)
		exit(1);
		// terminate(ERR_MEM, 1);
	if (ft_strlen(env_var) > 0 && getenv(env_var) == NULL)
	{
		remove_char[start - 1] = 1;
		while (start < *idx)
		{
			remove_char[start] = 1;
			start++;
		}
	}
	ft_delete(env_var);
}

void	remove_quotes(char *word, int *remove_char, int *single_quoted)
{
	ssize_t	idx;
	t_bool	f_single_quote;

	idx = -1;
	while (word[++idx])
	{
		if (word[idx] == '\'')
		{
			*single_quoted = 1;
			remove_char[idx] = 1;
			find_closing_quote(word, &idx, &f_single_quote, '\'');
			remove_char[idx] = 1;
		}
		if (word[idx] == '\"')
		{
			remove_char[idx] = 1;
			find_closing_quote(word, &idx, &f_single_quote, '\"');
			remove_char[idx] = 1;
		}
	}
}

void	format_word(char *word, int *remove_char)
{
	ssize_t	idx;
	ssize_t	count;
	ssize_t	word_len;
	char	*word_cpy;

	word_cpy = ft_strdup(word);
	if (word_cpy == NULL)
		exit(1); // terminate(ERR_MEM, 1);
	word_len = ft_strlen(word);
	idx = -1;
	count = 0;
	while (++idx < word_len)
	{
		if (remove_char[idx] == 0)
		{
			word[count] = word_cpy[idx];
			count++;
		}
	}
	while (count < word_len)
	{
		word[count] = '\0';
		count++;
	}
	ft_delete(word_cpy);
}

char	*expand_env(char *word, int exit_status, t_env *env)
{
	size_t	old_length;
	size_t	new_length;
	char	*cpy_word;

	new_length = new_word_length(word, exit_status, env);
	old_length = ft_strlen(word);
	cpy_word = ft_calloc(sizeof(char), old_length + 1);
	if (!cpy_word)
		exit(1); //	terminate(ERR_MEM, 1);
	ft_strlcpy(cpy_word, word, old_length + 1);
	ft_delete(word);
	word = ft_calloc(sizeof(char), new_length + 1);
	if (!word)
		exit(1); //	terminate(ERR_MEM, 1);
	set_new_word(word, cpy_word, exit_status, env);
	ft_delete(cpy_word);
	return (word);
}
