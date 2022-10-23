/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:12:26 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/23 12:02:06 by ogonzale         ###   ########.fr       */
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
		printf("%s\n", ((t_token_content *)lst_cpy->content)->word);
		lst_cpy = lst_cpy->next;
	}
	lst_cpy = 0;
}

void	split_and_classify(void *content)
{
	t_cmd_line_content	*cmd_line;
	t_token_content		*token_content;
	t_list				*token_node;
	char				**split_cmd;
	int					i;
	int					word_len;

	cmd_line = content;
	ft_split_mod(&split_cmd, cmd_line->cmd, ' ');
	cmd_line->word = NULL;
	i = 0;
	while (split_cmd[i] != NULL)
	{
		token_content = malloc(sizeof(t_token_content));
		if (token_content == NULL)
			terminate(ERR_MEM, 1);
		word_len = ft_strlen(split_cmd[i]);
		token_content->word = malloc(sizeof(char) * (word_len + 1));
		if (token_content->word == NULL)
			terminate(ERR_MEM, 1);
		ft_strlcpy(token_content->word, split_cmd[i], word_len + 1);
		token_node = ft_lstnew(token_content);	
		if (token_node == NULL)
			terminate(ERR_MEM, 1);
		ft_lstadd_back(&(cmd_line->word), token_node);
		i++;
	}
	ft_free_twod_memory(split_cmd);
}

void	split_words(t_list **cmd_line)
{
	t_list	*cmd_line_cpy;

	cmd_line_cpy = *cmd_line;
	ft_lstiter(cmd_line_cpy, &split_and_classify);
}
