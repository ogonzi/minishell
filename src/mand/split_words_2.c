/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:13:38 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/25 19:19:35 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"

int	add_new_word(char *split_cmd, t_word *word, t_list **token_node,
			t_cmd_line_content *cmd_line)
{
	word->str = ft_substr(split_cmd, word->start, word->end - word->start);
	if (word->str == NULL)
		terminate(ERR_MEM, 1);
	if (set_token_node(word->str, token_node, word->last_type) == 1)
		return (1);
	ft_lstadd_back(&(cmd_line->word), *token_node);
	free(word->str);
	word->start = word->end;
	return (0);
}

int	handle_redirection_split(char *split_cmd, t_list **token_node,
		enum e_type *last_word_type, t_cmd_line_content *cmd_line)
{
	t_word	word;

	word.start = 0;
	word.end = 0;
	word.last_type = last_word_type;
	while (split_cmd[word.end] != '\0')
	{
		while (split_cmd[word.end] != '<' && split_cmd[word.end] != '>'
			&& split_cmd[word.end] != '\0')
			word.end++;
		if (word.end != word.start)
		{
			if (add_new_word(split_cmd, &word, token_node, cmd_line) == 1)
				return (1);
		}
		if ((split_cmd[word.end] == '<' && split_cmd[word.end + 1] != '<')
			|| (split_cmd[word.end] == '>' && split_cmd[word.end + 1] != '>'))
		{
			word.end++;
			if (add_new_word(split_cmd, &word, token_node, cmd_line) == 1)
				return (1);
		}
		else if ((split_cmd[word.end] == '<' && split_cmd[word.end + 1] == '<')
			|| (split_cmd[word.end] == '>' && split_cmd[word.end + 1] == '>'))
		{
			word.end += 2;
			if (add_new_word(split_cmd, &word, token_node, cmd_line) == 1)
				return (1);
		}
	}
	return (0);
}

int	redirection_conditions(char *split_cmd)
{
	if (ft_strlen(split_cmd) > 1 && ft_is_in_set(split_cmd[0], "\'\"") == 0
		&& (ft_strchr(split_cmd, '<') != NULL
			|| ft_strchr(split_cmd, '>') != NULL))
		return (1);
	return (0);
}
