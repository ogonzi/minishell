/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:33:12 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/17 10:27:07 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_words(void *content)
{
	t_token_content	*token_content;

	token_content = content;
	free(token_content->word);
	token_content->word = NULL;
	free(token_content);
	token_content = NULL;
}

static void	ft_free_cmd_line_content(void *content)
{
	t_cmd_line_content	*cmd_line_content;
	t_list				*tmp;
	t_list				*words;

	cmd_line_content = content;
	free(cmd_line_content->cmd);
	cmd_line_content->cmd = NULL;
	words = cmd_line_content->word;
	ft_lstiter(words, &ft_free_words);
	while (words)
	{
		tmp = words->next;
		free(words);
		words = tmp;
	}
	words = NULL;
	free(cmd_line_content);
	cmd_line_content = NULL;
}

static void	ft_free_environ_content(void *content)
{
	t_environ_content	*environ_content;

	environ_content = content;
	free(environ_content->env_var);
	environ_content->env_var = NULL;
	free(environ_content);
	environ_content = NULL;
}

void	free_environ(t_list **environ)
{
	t_list	*tmp;

	ft_lstiter(*environ, &ft_free_environ_content);
	while (*environ)
	{
		tmp = (*environ)->next;
		free(*environ);
		*environ = tmp;
	}
	*environ = NULL;
}

void	free_cmd_line(t_list **cmd_line)
{
	t_list	*tmp;

	ft_lstiter(*cmd_line, &ft_free_cmd_line_content);
	while (*cmd_line)
	{
		tmp = (*cmd_line)->next;
		free(*cmd_line);
		*cmd_line = tmp;
	}
	*cmd_line = NULL;
}
