/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:12:26 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/08 18:34:33 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <stdio.h>

void	set_type_after_redir(enum e_type *last_word_type)
{
	if (*last_word_type == FILE_IN)
		*last_word_type = OPEN_FILE;
	else if (*last_word_type == HERE_DOC)
		*last_word_type = LIMITOR;
	else if (*last_word_type == FILE_OUT)
		*last_word_type = EXIT_FILE;
	else if (*last_word_type == FILE_OUT_APP)
		*last_word_type = EXIT_FILE_RET;
}

void	set_word_type(char *word, int word_len, enum e_type *last_word_type)
{
	if (*last_word_type == NONE || *last_word_type == ARG
		|| *last_word_type == OPEN_FILE || *last_word_type == LIMITOR
		|| *last_word_type == EXIT_FILE || *last_word_type == EXIT_FILE_RET)
	{
		if (ft_strncmp("<", word, word_len) == 0)
			*last_word_type = FILE_IN;
		else if (ft_strncmp("<<", word, word_len) == 0)
			*last_word_type = HERE_DOC;
		else if (ft_strncmp(">", word, word_len) == 0)
			*last_word_type = FILE_OUT;
		else if (ft_strncmp(">>", word, word_len) == 0)
			*last_word_type = FILE_OUT_APP;
		else
			*last_word_type = ARG;
	}
	else if (*last_word_type == FILE_IN || *last_word_type == HERE_DOC
		|| *last_word_type == FILE_OUT || *last_word_type == FILE_OUT_APP)
	{
		if (syntax_error(word) == 1)
			*last_word_type = SYN_ERROR;
		else
			set_type_after_redir(last_word_type);
	}
}

void	set_token_node(char *word, t_list **token_node,
			enum e_type *last_word_type)
{
	t_token_data		*token_data;
	int					word_len;

	word_len = ft_strlen(word);
	set_word_type(word, word_len, last_word_type);
	token_data = malloc(sizeof(t_token_data));
	if (token_data == NULL)
		terminate(ERR_MEM, 1);
	token_data->word = malloc(sizeof(char) * (word_len + 1));
	if (token_data->word == NULL)
		terminate(ERR_MEM, 1);
	token_data->type = *last_word_type;
	ft_strlcpy(token_data->word, word, word_len + 1);
	*token_node = ft_lstnew(token_data);
	if (*token_node == NULL)
		terminate(ERR_MEM, 1);
}

/*
 * This function first splits the command line into words, then goes
 * through each word, checking if a redirection is present in the word.
 * For example a>b (without spaces would be counted as 1 word). If the
 * case is given, a>b is split into a, >, b. Each added to the end of the
 * list. If not, the token node is set and added to the end of the list.
 */

void	split_and_classify(void *data)
{
	t_cmd_line_data	*cmd_line;
	t_list				*token_node;
	char				**split_cmd;
	int					i;
	enum e_type			last_word_type;

	cmd_line = data;
	ft_split_mod(&split_cmd, cmd_line->cmd, " \t\n");
	cmd_line->word = NULL;
	i = 0;
	last_word_type = NONE;
	while (split_cmd[i] != NULL)
	{
		if (redirection_conditions(split_cmd[i]) == 1)
			handle_redirection_split(split_cmd[i], &token_node,
				&last_word_type, cmd_line);
		else
		{
			set_token_node(split_cmd[i], &token_node, &last_word_type);
			ft_lstadd_back(&(cmd_line->word), token_node);
		}
		i++;
	}
	ft_free_twod_memory(split_cmd);
}

int	split_words(t_list **cmd_line)
{
	ft_lstforeach(*cmd_line, &split_and_classify);
	return (check_syntax_error(cmd_line));
}
