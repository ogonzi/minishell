/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:10:29 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/19 20:43:23 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_exec.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

static t_bool	handle_open_file(int *fd_in, int *did_redirection,
					char *filename);
static t_bool	do_here_doc(int *fd_in, char *limitor, int *did_redirection);
static t_bool	aux_here_doc(char *limitor);
static t_bool	line_is_limitor(char *line, char *limitor);

t_bool	dup_to_in(int *tmp_fd_in, t_list *command)
{
	t_list	*token;
	t_token	*token_content;
	int		fd_in;
	t_bool	did_redirection;

	token = ((t_cmdline *)command->data)->word;
	did_redirection = FALSE;
	while (token)
	{
		token_content = token->data;
		if (token_content->type == OPEN_FILE
			&& handle_open_file(&fd_in, &did_redirection,
				token_content->word) == TRUE)
			return (TRUE);
		else if (token_content->type == LIMITOR
			&& do_here_doc(&fd_in, token_content->word,
				&did_redirection) == TRUE)
			return (TRUE);
		token = token->next;
	}
	if (did_redirection == 1 && dup2(fd_in, *tmp_fd_in) == ERRNUM)
		terminate(ERR_DUP, EXIT_FAILURE);
	if (did_redirection == 1 && close(fd_in) != 0)
		terminate(ERR_CLOSE, EXIT_FAILURE);
	return (FALSE);
}

static t_bool	handle_open_file(int *fd_in, int *did_redirection,
	char *filename)
{
	if (*did_redirection == 1 && close(*fd_in) != 0)
		terminate(ERR_CLOSE, EXIT_FAILURE);
	*fd_in = open(filename, O_RDONLY);
	if (*fd_in < 0)
	{
		ft_printf_fd(STDERR_FILENO, "msh: %s: Error reading file or \
		directory\n", filename);
		return (TRUE);
	}
	*did_redirection = 1;
	return (FALSE);
}

static t_bool	do_here_doc(int *fd_in, char *limitor, int *did_redirection)
{
	pid_t	pid;

	set_sigint_action_heredoc();
	pid = fork();
	if (pid == -1)
		terminate(ERR_FORK, EXIT_FAILURE);
	else if (pid == 0)
	{
		while (42)
			if (!aux_here_doc(limitor))
				break ;
	}
	if (*did_redirection == 1 && close(*fd_in) != 0)
		terminate(ERR_CLOSE, EXIT_FAILURE);
	*fd_in = open(TMP_FILE_HEREDOC, O_RDONLY | O_CREAT);
	if (*fd_in < 0)
	{
		ft_printf_fd(STDERR_FILENO, "msh: %s: Error reading file or \
		directory\n", limitor);
		return (TRUE);
	}
	if (unlink(TMP_FILE_HEREDOC) != 0)
		terminate(ERR_UNLINK, EXIT_FAILURE);
	*did_redirection = 1;
	return (FALSE);
}

static t_bool	aux_here_doc(char *limitor)
{
	char	*line;
	int		tmp_fd;

	write(STDOUT_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	if (!line)
	{
		ft_printf_fd(STDERR_FILENO, "msh: warning: here-document delimited\
			by end-of-file (wanted `%s')\n", limitor);
		return (FALSE);
	}
	if (line_is_limitor(line, limitor))
	{
		ft_delete(line);
		return (FALSE);
	}
	tmp_fd = open(TMP_FILE_HEREDOC, O_WRONLY | O_APPEND | O_CREAT, 0600);
	if (tmp_fd < 0)
		terminate(ERR_OPEN, EXIT_FAILURE);
	write(tmp_fd, line, ft_strlen(line));
	if (close(tmp_fd) != 0)
		terminate(ERR_CLOSE, EXIT_FAILURE);
	ft_delete(line);
	return (TRUE);
}

static t_bool	line_is_limitor(char *line, char *limitor)
{
	int	length_line;
	int	length_limitor;

	length_line = ft_strlen(line) - 1;
	length_limitor = ft_strlen(limitor);
	if (length_line >= length_limitor
		&& !ft_strncmp(line, limitor, length_line))
		return (TRUE);
	else if (length_line < length_limitor
		&& !ft_strncmp(line, limitor, length_limitor))
		return (TRUE);
	return (FALSE);
}
