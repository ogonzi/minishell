/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:33:12 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/13 17:03:14 by ogonzale         ###   ########.fr       */
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

void	ft_free_cmd_line_content(void *content)
{
	t_cmd_line_content	*cmd_line_content;

	cmd_line_content = content;
	free(cmd_line_content->cmd);
	cmd_line_content->cmd = NULL;
	free_word_list(&(cmd_line_content->word));
	free(cmd_line_content);
	cmd_line_content = NULL;
}

void	ft_free_environ_content(void *content)
{
	t_environ_content	*environ_content;

	environ_content = content;
	free(environ_content->env_var);
	environ_content->env_var = NULL;
	free(environ_content);
	environ_content = NULL;
}

void	free_all(t_prompt *prompt)
{
	t_list	*tmp;

	ft_lstiter(prompt->cmd_line, &ft_free_cmd_line_content);
	while (prompt->cmd_line)
	{
		tmp = prompt->cmd_line->next;
		free(prompt->cmd_line);
		prompt->cmd_line = tmp;
	}
	ft_lstiter(prompt->environ, &ft_free_environ_content);
	while (prompt->environ)
	{
		tmp = prompt->environ->next;
		free(prompt->environ);
		prompt->environ = tmp;
	}
	prompt->cmd_line = NULL;
	prompt->environ = NULL;
}
