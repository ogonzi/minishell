/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:13:38 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/09 18:51:22 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"

void	add_new_word(char *split_cmd, t_word *word, t_list **token_node,
			t_cmd_line_content *cmd_line)
{
	word->str = ft_substr(split_cmd, word->start, word->end - word->start);
	if (word->str == NULL)
		terminate(ERR_MEM, 1);
	set_token_node(word->str, token_node, word->last_type);
	ft_lstadd_back(&(cmd_line->word), *token_node);
	free(word->str);
	word->start = word->end;
}

void	handle_redirection_split(char *split_cmd, t_list **token_node,
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
		{
			move_to_end_of_quote(split_cmd, &word.end);
			word.end++;
		}
		if (word.end != word.start)
			add_new_word(split_cmd, &word, token_node, cmd_line);
		if ((split_cmd[word.end] == '<' && split_cmd[word.end + 1] != '<')
			|| (split_cmd[word.end] == '>' && split_cmd[word.end + 1] != '>'))
		{
			word.end++;
			add_new_word(split_cmd, &word, token_node, cmd_line);
		}
		else if ((split_cmd[word.end] == '<' && split_cmd[word.end + 1] == '<')
			|| (split_cmd[word.end] == '>' && split_cmd[word.end + 1] == '>'))
		{
			word.end += 2;
			add_new_word(split_cmd, &word, token_node, cmd_line);
		}
	}
}

int	redirection_conditions(char *split_cmd)
{
	if (ft_strlen(split_cmd) > 1
		&& (ft_strchr(split_cmd, '<') != NULL
			|| ft_strchr(split_cmd, '>') != NULL))
		return (1);
	return (0);
}

int	check_syntax_error(t_list **cmd_line)
{
	t_cmd_line_content	*cmd_line_content;
	t_list				*cmd_line_cpy;

	cmd_line_cpy = *cmd_line;
	while (cmd_line_cpy)
	{
		cmd_line_content = cmd_line_cpy->content;
		while (cmd_line_content->word)
		{
			if (((t_token_content *)cmd_line_content->word->content)->type
				== SYN_ERROR)
				return (2);
			cmd_line_content->word = cmd_line_content->word->next;
		}
		cmd_line_cpy = cmd_line_cpy->next;
	}
	return (0);
}
