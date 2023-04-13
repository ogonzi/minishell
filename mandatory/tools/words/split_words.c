/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:48:43 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/13 15:44:40 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_words.h"
#include "mnshll_parser.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

typedef struct s_classify
{
	enum e_type	last_word_type;
	t_cmdline	*cmdline;
	t_list		*token;
	ssize_t		idx;
	char		**split_cmd;
	char		*aux;
}t_classify;

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
	t_classify	class;

	class.idx = -1;
	class.cmdline = content;
	class.cmdline->word = NULL;
	class.last_word_type = NONE;
	ft_split_mod(&class.split_cmd, class.cmdline->cmd, " \t\n");
	while (class.split_cmd[++class.idx])
	{
		class.aux = ft_strdup(class.split_cmd[class.idx]);
		if (!class.aux)
			terminate(ERR_MEM, EXIT_FAILURE);
		if (redirection_conditions(class.aux))
			handle_redirection_split(class.aux, &class.token,
				&class.last_word_type, class.cmdline);
		else
		{
			set_token_node(class.aux, &class.token, &class.last_word_type);
			ft_lstadd_back(&(class.cmdline->word), class.token);
		}
		ft_delete(class.aux);
	}
	ft_memfree(class.split_cmd);
}
