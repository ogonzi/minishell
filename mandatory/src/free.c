/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:33:12 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/08 18:34:33 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	ft_free_words(void *data)
{
	t_token_data	*token_data;

	token_data = data;
	free(token_data->word);
	token_data->word = NULL;
	free(token_data);
	token_data = NULL;
}

void	free_word_list(t_list **words)
{
	t_list	*tmp;

	ft_lstforeach(*words, &ft_free_words);
	while (*words)
	{
		tmp = (*words)->next;
		free(*words);
		*words = tmp;
	}
	*words = NULL;
}

void	ft_free(void *data)
{
	t_cmd_line_data	*cmd_line_data;

	cmd_line_data = data;
	free(cmd_line_data->cmd);
	cmd_line_data->cmd = NULL;
	free_word_list(&(cmd_line_data->word));
	free(cmd_line_data);
	cmd_line_data = NULL;
}

void	free_cmd_line(t_list **cmd_line)
{
	t_list	*tmp;

	ft_lstforeach(*cmd_line, &ft_free);
	while (*cmd_line)
	{
		tmp = (*cmd_line)->next;
		free(*cmd_line);
		*cmd_line = tmp;
	}
	*cmd_line = NULL;
}
