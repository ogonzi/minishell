/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:46:53 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/09 18:10:47 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

static void	set_type_after_redir(enum e_type *last_word_type);

void	set_token_node(char *word, t_list **token_node,
			enum e_type *last_word_type)
{
	t_token	*token_data;
	size_t	word_len;

	word_len = ft_strlen(word);
	set_word_type(word, word_len, last_word_type);
	token_data = (t_token *)malloc(sizeof(t_token));
	if (!token_data)
		exit(1);
		// terminate(ERR_MEM, 1);
	token_data->word = malloc(sizeof(char) * (word_len + 1));
	if (!token_data->word)
		exit(1);
		// terminate(ERR_MEM, 1);
	token_data->type = *last_word_type;
	ft_strlcpy(token_data->word, word, word_len + 1);
	*token_node = ft_lstnew(token_data);
	if (!(*token_node))
		exit(1);
		// terminate(ERR_MEM, 1);
}

void	set_word_type(char *word, size_t word_len, enum e_type *last_word_type)
{
	if (*last_word_type == NONE || *last_word_type == ARG
		|| *last_word_type == OPEN_FILE || *last_word_type == LIMITOR
		|| *last_word_type == EXIT_FILE || *last_word_type == EXIT_FILE_APP)
	{
		if (!ft_strncmp("<", word, word_len))
			*last_word_type = FILE_IN;
		else if (!ft_strncmp("<<", word, word_len))
			*last_word_type = HERE_DOC;
		else if (!ft_strncmp(">", word, word_len))
			*last_word_type = FILE_OUT;
		else if (!ft_strncmp(">>", word, word_len))
			*last_word_type = FILE_OUT_APP;
		else
			*last_word_type = ARG;
	}
	else if (*last_word_type == FILE_IN || *last_word_type == HERE_DOC
		|| *last_word_type == FILE_OUT || *last_word_type == FILE_OUT_APP)
	{
		if (syntax_error(word))
			*last_word_type = SYN_ERROR;
		else
			set_type_after_redir(last_word_type);
	}
}

static void	set_type_after_redir(enum e_type *last_word_type)
{
	if (*last_word_type == FILE_IN)
		*last_word_type = OPEN_FILE;
	else if (*last_word_type == HERE_DOC)
		*last_word_type = LIMITOR;
	else if (*last_word_type == FILE_OUT)
		*last_word_type = EXIT_FILE;
	else if (*last_word_type == FILE_OUT_APP)
		*last_word_type = EXIT_FILE_APP;
}
