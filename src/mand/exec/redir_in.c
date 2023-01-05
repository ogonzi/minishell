/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:54:18 by ogonzale          #+#    #+#             */
/*   Updated: 2023/01/05 19:04:29 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

static int	line_is_limitor(char *line, char *limitor)
{
	int	length_line;
	int	length_limitor;

	length_line = ft_strlen(line) - 1;
	length_limitor = ft_strlen(limitor);
	if (length_line >= length_limitor
		&& ft_strncmp(line, limitor, length_line) == 0)
		return (1);
	else if (length_line < length_limitor
		&& ft_strncmp(line, limitor, length_limitor) == 0)
		return (1);
	return (0);
}

static int	heredoc_continues(char *limitor)
{
	char	*line;
	int		tmp_fd;

	write(STDOUT_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	if (line == NULL)
	{
		printf("msh: warning: here-document delimited by end-of-file"
			" (wanted `%s')\n", limitor);
		return (0);
	}
	if (line_is_limitor(line, limitor))
		return (0);
	tmp_fd = open(TMP_FILE_HEREDOC, O_WRONLY | O_APPEND | O_CREAT, 0600);
	if (tmp_fd < 0)
		terminate(ERR_OPEN, 1);
	write(tmp_fd, line, ft_strlen(line));
	if (close(tmp_fd) != 0)
		terminate(ERR_CLOSE, 1);
	free(line);
	line = NULL;
	return (1);
}

// BUG: When there is more than one heredoc input, cat << EOF << CAT,
// weird stuff happens
static int	do_here_doc(int *fd_in, char *limitor, int *did_redirection)
{
	while (heredoc_continues(limitor))
		;
	if (*did_redirection == 1 && close(*fd_in) != 0)
		terminate(ERR_CLOSE, 1);
	*fd_in = open(TMP_FILE_HEREDOC, O_RDONLY | O_CREAT);
	if (*fd_in < 0)
	{
		printf("msh: %s: Error reading file or directory\n", limitor);
		return (1);
	}
	unlink(TMP_FILE_HEREDOC);
	*did_redirection = 1;
	return (0);
}

static int	handle_open_file(int *fd_in, int *did_redirection, char *filename)
{
	if (*did_redirection == 1 && close(*fd_in) != 0)
		terminate(ERR_CLOSE, 1);
	*fd_in = open(filename, O_RDONLY);
	if (*fd_in < 0)
	{
		printf("msh: %s: Error reading file or directory\n", filename);
		return (1);
	}
	*did_redirection = 1;
	return (0);
}

int	dup_to_in(int *tmp_fd_in, t_list *command)
{
	t_list			*token;
	t_token_content	*token_content;
	int				fd_in;
	int				did_redirection;

	token = ((t_cmd_line_content *)command->content)->word;
	did_redirection = 0;
	while (token)
	{
		token_content = token->content;
		if (token_content->type == OPEN_FILE
			&& handle_open_file(&fd_in, &did_redirection,
				token_content->word) == 1)
			return (1);
		else if (token_content->type == LIMITOR
			&& do_here_doc(&fd_in, token_content->word,
				&did_redirection) == 1)
			return (1);
		token = token->next;
	}
	if (did_redirection == 1 && dup2(fd_in, *tmp_fd_in) == -1)
		terminate(ERR_DUP, 1);
	if (did_redirection == 1 && close(fd_in) != 0)
		terminate(ERR_CLOSE, 1);
	return (0);
}
