/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:10:51 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/09 12:38:00 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

static t_bool	handle_write_to_exit_file(int *fd_out, t_bool *did_redirection,
		t_token *token_content);

t_bool	dup_to_out(int *tmp_fd_out, t_list *command, int *did_out_redirection)
{
	t_list	*token;
	t_token	*token_content;
	t_bool	did_redirection;
	int		fd_out;

	did_redirection = FALSE;
	token = ((t_cmdline *)command->data)->word;
	while (token)
	{
		token_content = token->data;
		if (handle_write_to_exit_file(&fd_out,
				&did_redirection, token_content))
			return (TRUE);
		token = token->next;
	}
	if (did_redirection == TRUE && dup2(fd_out, *tmp_fd_out) == ERRNUM)
		exit(1); // terminate(ERR_DUP, 1);
	if (did_redirection == TRUE && close(fd_out))
		exit(1); // terminate(ERR_CLOSE, 1);
	*did_out_redirection = did_redirection;
	return (FALSE);
}

static t_bool	handle_write_to_exit_file(int *fd_out, t_bool *did_redirection,
		t_token *token_content)
{
	if (token_content->type == EXIT_FILE
		|| token_content->type == EXIT_FILE_APP)
	{
		if (*did_redirection == TRUE && close(*fd_out))
			exit(EXIT_FAILURE); // terminate(ERR_CLOSE, 1);
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
			return (TRUE);
		}
		*did_redirection = TRUE;
	}
	return (FALSE);
}
