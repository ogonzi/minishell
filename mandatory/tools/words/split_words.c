/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:48:43 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/10 12:55:25 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_words.h"
#include "mnshll_parser.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

void	split_and_classify(void *content);

int	split_words(t_prompt *prompt)
{
	ft_lstforeach(prompt->cmdline, &split_and_classify);
	return (check_syntax_error(&prompt->cmdline));
}

void	split_and_classify(void *content)
/*
 * This function is responsible for splitting a command line into tokens and
 * classifying them based on their type.

 * The function takes a pointer to a t_cmdline struct as its argument.
 * This struct contains a cmd field, which is a string that represents the
 * command line to be split, and a word field, which is a linked list that will
 * hold the classified tokens.

 * The function first uses the ft_split_mod function to split the command line
 * string into an array of strings using the delimiter characters " \t\n".
 * It then iterates through each string in the array and checks whether it
 * satisfies the conditions for redirection. If it does, the function
 * handle_redirection_split is called to handle the redirection and set the
 * appropriate last_word_type and token values. If it does not satisfy the
 * redirection conditions, the function set_token_node is called to set the
 * appropriate last_word_type and token values.

 * Finally, the function adds the token to the end of the word linked list using
 * the ft_lstadd_back function.

 * Once all the strings in the split_cmd array have been processed, the function
 * frees the memory allocated for the split_cmd array using ft_memfree.
*/
{
	enum e_type	last_word_type;
	t_cmdline	*cmdline;
	t_list		*token;
	ssize_t		idx;
	char		**split_cmd;

	idx = -1;
	cmdline = content;
	cmdline->word = NULL;
	last_word_type = NONE;
	ft_split_mod(&split_cmd, cmdline->cmd, " \t\n");
	while (split_cmd[++idx])
	{
		if (redirection_conditions(split_cmd[idx]))
			handle_redirection_split(split_cmd[idx], &token,
				&last_word_type, cmdline);
		else
		{
			set_token_node(split_cmd[idx], &token, &last_word_type);
			ft_lstadd_back(&(cmdline->word), token);
		}
	}
	ft_memfree(split_cmd);
}
