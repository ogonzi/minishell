/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:38:07 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/15 17:37:53 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <stdio.h>

void	print_list(t_list *lst)
{
	t_list				*lst_cpy;

	lst_cpy = lst;
	while (lst_cpy)
	{
		printf("%s (%d)\n", ((t_token_content *)lst_cpy->content)->word,
			((t_token_content *)lst_cpy->content)->type);
		lst_cpy = lst_cpy->next;
	}
	lst_cpy = 0;
}

void	expand(char *word)
{
	int		i;
	int		start;
	int		single_quote_flag;
	char	*env_var;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '\'')
			find_closing_quote(word, &i, &single_quote_flag, '\'');
		if (word[i] == '$' && (i == 0 || word[i - 1] != '\\'))
		{
			i++;
			start = i;
			while (ft_is_in_set(word[i], " \t\r\"\0") == 0)
				i++;
			env_var = ft_substr(word, start, i - start);
			printf("%s\n", env_var);
		}
		i++;
	}
}

int	expand_words(t_list **cmd_line)
{
	t_list	*cmd_line_cpy;
	t_list	*word_cpy;

	cmd_line_cpy = *cmd_line;
	while (cmd_line_cpy)
	{
		word_cpy = ((t_cmd_line_content *)cmd_line_cpy->content)->word;
		while (word_cpy)
		{
			expand(((t_token_content *)word_cpy->content)->word);
			word_cpy = word_cpy->next;
		}
		cmd_line_cpy = cmd_line_cpy->next; 
	}
	return (0);
}
