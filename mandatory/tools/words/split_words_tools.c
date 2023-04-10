/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:16:52 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/10 12:55:45 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_words.h"
#include "mnshll_parser.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

void	handle_redirection_split(char *split_cmd, t_list **token,
		enum e_type *last_word_type, t_cmdline *cmdline)
{
	t_word	word;

	init_word(&word, last_word_type);
	while (split_cmd[word.end])
	{
		while (split_cmd[word.end] != '<' && split_cmd[word.end] != '>'
			&& split_cmd[word.end] != '\0')
		{
			move_to_end_of_quote(split_cmd, &word.end);
			word.end++;
		}
		if (word.end != word.start)
			add_new_word(split_cmd, &word, token, cmdline);
		if (is_single_redirection(split_cmd, word.end))
		{
			word.end++;
			add_new_word(split_cmd, &word, token, cmdline);
		}
		else if (is_double_redirection(split_cmd, word.end))
		{
			word.end += 2;
			add_new_word(split_cmd, &word, token, cmdline);
		}
	}
}

void	add_new_word(char *split_cmd, t_word *word, t_list **token,
			t_cmdline *cmdline)
{
	word->str = ft_substr(split_cmd, word->start, word->end - word->start);
	if (word->str == NULL)
		terminate(ERR_MEM, EXIT_FAILURE);
	set_token_node(word->str, token, word->last_type);
	ft_lstadd_back(&(cmdline->word), *token);
	ft_delete(word->str);
	word->start = word->end;
}
