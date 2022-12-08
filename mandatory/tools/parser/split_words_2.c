/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:13:38 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/08 16:19:53 by cpeset-c         ###   ########.fr       */
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
	t_cmd_line_data	*cmd_line_data;
	t_list				*cmd_line_cpy;
	t_list				*word_cpy;

	cmd_line_cpy = *cmd_line;
	while (cmd_line_cpy)
	{
		cmd_line_data = cmd_line_cpy->data;
		word_cpy = cmd_line_data->word;
		while (word_cpy)
		{
			if (((t_token_data *)word_cpy->data)->type
				== SYN_ERROR)
				return (2);
			word_cpy = word_cpy->next;
		}
		cmd_line_cpy = cmd_line_cpy->next;
	}
	return (0);
}
