/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:39:23 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/08 12:51:26 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

void	expand_words(t_prompt *prompt)
{
	t_list	*l_cmd_line_cpy;
	t_list	*l_word_cpy;
	char	*word;
	int		single_quoted;

	l_cmd_line_cpy = prompt->cmdline;
	while (l_cmd_line_cpy)
	{
		l_word_cpy = (t_list *)((t_cmdline *)l_cmd_line_cpy->data)->word;
		while (l_word_cpy)
		{
			single_quoted = FALSE;
			word = ((t_token *)l_word_cpy->data)->word;
			handle_word_expansion(word, &single_quoted);
			if (ft_strchr(word, '$') && single_quoted == FALSE)
				((t_token *)l_word_cpy->data)->word
					= expand_env(word, prompt->exit_status, prompt->env);
			l_word_cpy = l_word_cpy->next;
		}
		l_cmd_line_cpy = l_cmd_line_cpy->next;
	}
}

void	handle_word_expansion(char *word, int *single_quoted)
{
	int	*remove_char;

	*single_quoted = FALSE;
	remove_char = ft_calloc(ft_strlen(word) + 1, sizeof(int));
	if (!remove_char)
		exit(1); // 	terminate(ERR_MEM, 1);
	expand(word, remove_char);
	remove_quotes(word, remove_char, single_quoted);
	format_word(word, remove_char);
	ft_delete(remove_char);
}

void	expand(char *word, int *remove_char)
{
	ssize_t		idx;
	t_bool		single_quote_flag;
	t_bool		is_double_quoted;

	idx = 0;
	is_double_quoted = FALSE;
	while (word[idx])
	{
		if (word[idx] == '\"')
			set_opposite_binary(&is_double_quoted);
		if (word[idx] == '\'' && is_double_quoted == FALSE)
			find_closing_quote(word, &idx, &single_quote_flag, '\'');
		if (word[idx] == '$' && (idx == 0 || word[idx - 1] != '\\'))
			handle_expand_env_var(word, &idx, remove_char);
		else
			idx++;
	}
}
