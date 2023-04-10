/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:50:55 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/10 12:55:56 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_words.h"
#include "mnshll_parser.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

int	check_syntax_error(t_list **cmdline)
{
	t_cmdline	*cmd_line_content;
	t_list		*cmd_line_cpy;
	t_list		*word_cpy;
	int			type;

	cmd_line_cpy = *cmdline;
	while (cmd_line_cpy)
	{
		cmd_line_content = cmd_line_cpy->data;
		word_cpy = cmd_line_content->word;
		while (word_cpy)
		{
			type = ((t_token *)word_cpy->data)->type;
			if (type == SYN_ERROR)
				return (SHELL_MISUSE);
			if (word_cpy->next == NULL && (type == FILE_IN
					|| type == HERE_DOC || type == FILE_OUT
					|| type == FILE_OUT_APP) && ft_perror_syntax("`newline'"))
				return (SHELL_MISUSE);
			word_cpy = word_cpy->next;
		}
		cmd_line_cpy = cmd_line_cpy->next;
	}
	return (0);
}

t_bool	redirection_conditions(char *split_cmd)
{
	if (ft_strlen(split_cmd) > 1
		&& (ft_strchr(split_cmd, '<') != NULL
			|| ft_strchr(split_cmd, '>') != NULL))
		return (TRUE);
	return (FALSE);
}

void	init_word(t_word *word, enum e_type *last_word_type)
{
	word->start = 0;
	word->end = 0;
	word->last_type = last_word_type;
}

t_bool	is_single_redirection(char *split_cmd, int word_end)
{
	if ((split_cmd[word_end] == '<' && split_cmd[word_end + 1] != '<')
		|| (split_cmd[word_end] == '>' && split_cmd[word_end + 1] != '>'))
		return (TRUE);
	return (FALSE);
}

t_bool	is_double_redirection(char *split_cmd, int word_end)
{
	if ((split_cmd[word_end] == '<' && split_cmd[word_end + 1] == '<')
		|| (split_cmd[word_end] == '>' && split_cmd[word_end + 1] == '>'))
		return (TRUE);
	return (FALSE);
}
