/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:13:38 by ogonzale          #+#    #+#             */
/*   Updated: 2023/01/07 19:12:41 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"

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
	t_list				*word_cpy;
	int					type;

	cmd_line_cpy = *cmd_line;
	while (cmd_line_cpy)
	{
		cmd_line_content = cmd_line_cpy->content;
		word_cpy = cmd_line_content->word;
		while (word_cpy)
		{
			type = ((t_token_content *)word_cpy->content)->type;
			if (type == SYN_ERROR)
				return (SHELL_MISUSE);
			if (word_cpy->next == NULL && (type == FILE_IN
					|| type == HERE_DOC || type == FILE_OUT
					|| type == FILE_OUT_APP) && print_error_syntax("`newline'"))
				return (SHELL_MISUSE);
			word_cpy = word_cpy->next;
		}
		cmd_line_cpy = cmd_line_cpy->next;
	}
	return (0);
}
