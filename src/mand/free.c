/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:33:12 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/23 12:13:28 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	ft_free_words(void *content)
{
	t_token_content	*token_content;

	token_content = content;
	free(token_content->word);
	token_content->word = NULL;
	free(token_content);
	token_content = NULL;
}

void	free_word_list(t_list **words)
{
	t_list	*tmp;

	ft_lstiter(*words, &ft_free_words);
	while (*words)
	{
		tmp = (*words)->next;
		free(*words);
		*words = tmp;
	}
	*words = NULL;
}

void	ft_free(void *content)
{
	t_cmd_line_content	*cmd_line_content;

	cmd_line_content = content;
	free(cmd_line_content->cmd);
	cmd_line_content->cmd = NULL;
	free_word_list(&(cmd_line_content->word));
	free(cmd_line_content);
	cmd_line_content = NULL;
}

void	free_cmd_line(t_list **cmd_line)
{
	t_list	*tmp;

	ft_lstiter(*cmd_line, &ft_free);
	while (*cmd_line)
	{
		tmp = (*cmd_line)->next;
		free(*cmd_line);
		*cmd_line = tmp;
	}
	*cmd_line = NULL;
}
