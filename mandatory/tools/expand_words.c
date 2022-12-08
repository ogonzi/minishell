/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:38:07 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/08 16:19:53 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <stdio.h>

void	remove_quotes(char *word, int *remove_char)
{
	int	i;
	int	single_quote_flag;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '\'')
		{
			remove_char[i] = 1;
			find_closing_quote(word, &i, &single_quote_flag, '\'');
			remove_char[i] = 1;
		}
		if (word[i] == '\"')
		{
			remove_char[i] = 1;
			find_closing_quote(word, &i, &single_quote_flag, '\"');
			remove_char[i] = 1;
		}
		i++;
	}
}

void	format_word(char *word, int *remove_char)
{
	int		i;
	int		j;
	int		word_len;
	char	*word_cpy;

	word_cpy = ft_strdup(word);
	if (word_cpy == NULL)
		terminate(ERR_MEM, 1);
	word_len = ft_strlen(word);
	i = -1;
	j = 0;
	while (++i < word_len)
	{
		if (remove_char[i] == 0)
		{
			word[j] = word_cpy[i];
			j++;
		}
	}
	while (j < word_len)
	{
		word[j] = '\0';
		j++;
	}
	free(word_cpy);
}

void	alloc_remove_char(int **remove_char, char *word)
{
	int	word_len;
	int	i;

	word_len = ft_strlen(word);
	*remove_char = malloc(sizeof(int) * word_len);
	if (*remove_char == NULL)
		terminate(ERR_MEM, 1);
	i = -1;
	while (++i < word_len)
		(*remove_char)[i] = 0;
}

int	expand_words(t_list **l_cmd_line)
{
	t_list	*l_cmd_line_cpy;
	t_list	*l_word_cpy;
	char	*word;
	int		*remove_char;

	l_cmd_line_cpy = *l_cmd_line;
	while (l_cmd_line_cpy)
	{
		l_word_cpy = ((t_cmd_line_data *)l_cmd_line_cpy->data)->word;
		while (l_word_cpy)
		{
			word = ((t_token_data *)l_word_cpy->data)->word;
			alloc_remove_char(&remove_char, word);
			expand(word, remove_char);
			remove_quotes(word, remove_char);
			format_word(word, remove_char);
			free(remove_char);
			if (ft_strchr(word, '$'))
				((t_token_data *)l_word_cpy->data)->word
					= expand_env(word);
			l_word_cpy = l_word_cpy->next;
		}
		l_cmd_line_cpy = l_cmd_line_cpy->next;
	}
	return (0);
}
