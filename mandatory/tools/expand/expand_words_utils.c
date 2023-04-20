/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:55:16 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/20 20:31:57 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_expand.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

int	new_word_length(char *word, int exit_status, t_env *env)
{
	t_expander_wlen	exp_word_len;

	exp_word_len.idx = 0;
	exp_word_len.base_length = 0;
	exp_word_len.added_length = 0;
	while (word[exp_word_len.idx])
	{
		if (!get_added_length(word, &exp_word_len, exit_status, env))
		{
			exp_word_len.base_length++;
			exp_word_len.idx++;
		}
	}
	return (exp_word_len.base_length + exp_word_len.added_length);
}

t_bool	get_added_length(char *word, t_expander_wlen *exp_word_len,
	int exit_status, t_env *env)
{
	if (word[exp_word_len->idx] == '$'
		&& (ft_isalnum(word[exp_word_len->idx + 1])
			|| word[exp_word_len->idx + 1] == '_'))
	{
		(exp_word_len->idx)++;
		exp_word_len->added_length += get_env_var_length(word,
				&exp_word_len->idx, env);
		return (TRUE);
	}
	if (word[exp_word_len->idx] == '$' && word[exp_word_len->idx + 1] == '?')
	{
		exp_word_len->added_length += ft_nbrlen(exit_status);
		exp_word_len->idx += 2;
		return (TRUE);
	}
	return (FALSE);
}

void	copy_char_to_word(char *word, char *cpy_word,
		int *from_index, int *to_index)
{
	word[*to_index] = cpy_word[*from_index];
	(*from_index)++;
	(*to_index)++;
}

void	set_exit_status_to_word(char *word, int exit_status, int *i, int *j)
{
	char	*exit_status_str;
	int		k;

	*i += 2;
	exit_status_str = ft_itoa(exit_status);
	k = 0;
	while (exit_status_str[k])
		copy_char_to_word(word, exit_status_str, &k, j);
	ft_delete(exit_status_str);
}
