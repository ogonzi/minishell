/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:54:24 by ogonzale          #+#    #+#             */
/*   Updated: 2023/01/06 10:36:11 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

static int	handle_write_to_exit_file(int *fd_out, int *did_redirection,
								t_token_content *token_content)
{
	if (token_content->type == EXIT_FILE
		|| token_content->type == EXIT_FILE_APP)
	{
		if (*did_redirection == 1 && close(*fd_out) != 0)
			terminate(ERR_CLOSE, 1);
		if (token_content->type == EXIT_FILE)
			*fd_out = open(token_content->word,
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (token_content->type == EXIT_FILE_APP)
			*fd_out = open(token_content->word,
					O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (*fd_out < 0)
		{
			printf("msh: %s: Error writing file or directory\n",
				token_content->word);
			return (1);
		}
		*did_redirection = 1;
	}
	return (0);
}

/**
 * Loops through the tokens in the command, and calls
 * handle_write_to_exit_file. If a redirection is performed,
 * fd_out is dupped to tmp_fd_out (tmp_fd[1]).
*/
int	dup_to_out(int *tmp_fd_out, t_list *command, int *did_out_redirection)
{
	t_list			*token;
	t_token_content	*token_content;
	int				did_redirection;
	int				fd_out;

	did_redirection = 0;
	token = ((t_cmd_line_content *)command->content)->word;
	while (token)
	{
		token_content = token->content;
		if (handle_write_to_exit_file(&fd_out,
				&did_redirection, token_content) == 1)
			return (1);
		token = token->next;
	}
	if (did_redirection == 1 && dup2(fd_out, *tmp_fd_out) == -1)
		terminate(ERR_DUP, 1);
	if (did_redirection == 1 && close(fd_out) != 0)
		terminate(ERR_CLOSE, 1);
	*did_out_redirection = did_redirection;
	return (0);
}
