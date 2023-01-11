/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:54:10 by ogonzale          #+#    #+#             */
/*   Updated: 2023/01/11 13:29:11 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"
#include "minishell.h"

void	add_new_word(char *split_cmd, t_word *word, t_list **token_node,
			t_cmd_line_data *cmd_line)
{
	word->str = ft_substr(split_cmd, word->start, word->end - word->start);
	if (word->str == NULL)
		terminate(ERR_MEM, 1);
	set_token_node(word->str, token_node, word->last_type);
	ft_lstadd_back(&(cmd_line->word), *token_node);
	free(word->str);
	word->start = word->end;
}

void	init_word(t_word *word, enum e_type *last_word_type)
{
	word->start = 0;
	word->end = 0;
	word->last_type = last_word_type;
}

int	is_single_redirection(char *split_cmd, int word_end)
{
	if ((split_cmd[word_end] == '<' && split_cmd[word_end + 1] != '<')
		|| (split_cmd[word_end] == '>' && split_cmd[word_end + 1] != '>'))
		return (1);
	return (0);
}

int	is_double_redirection(char *split_cmd, int word_end)
{
	if ((split_cmd[word_end] == '<' && split_cmd[word_end + 1] == '<')
		|| (split_cmd[word_end] == '>' && split_cmd[word_end + 1] == '>'))
		return (1);
	return (0);
}

void	handle_redirection_split(char *split_cmd, t_list **token_node,
		enum e_type *last_word_type, t_cmd_line_data *cmd_line)
{
	t_word	word;

	init_word(&word, last_word_type);
	while (split_cmd[word.end] != '\0')
	{
		while (split_cmd[word.end] != '<' && split_cmd[word.end] != '>'
			&& split_cmd[word.end] != '\0')
		{
			move_to_end_of_quote(split_cmd, &word.end);
			word.end++;
		}
		if (word.end != word.start)
			add_new_word(split_cmd, &word, token_node, cmd_line);
		if (is_single_redirection(split_cmd, word.end))
		{
			word.end++;
			add_new_word(split_cmd, &word, token_node, cmd_line);
		}
		else if (is_double_redirection(split_cmd, word.end))
		{
			word.end += 2;
			add_new_word(split_cmd, &word, token_node, cmd_line);
		}
	}
}
