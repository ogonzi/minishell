/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:10:22 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/24 11:31:54 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

static void set_command_array(t_list *token_list, char ***command_array,
							  int len_list)
{
	int i;

	i = 0;
	while (token_list)
	{
		if (((t_token_content *)token_list->content)->type == 1)
		{
			(*command_array)[i] = ft_strdup(((t_token_content *)token_list->content)->word);
			if ((*command_array)[i] == NULL)
				terminate(ERR_MEM, 1);
			i++;
		}
		token_list = token_list->next;
	}
	while (i < len_list + 1)
	{
		(*command_array)[i] = NULL;
		i++;
	}
}

char **get_command_array(t_list *command)
{
	char **command_array;
	t_list *token_list;
	int len_list;

	token_list = ((t_cmd_line_content *)command->content)->word;
	len_list = ft_lstsize(token_list);
	command_array = malloc(sizeof(char *) * (len_list + 1));
	if (command_array == NULL)
		terminate(ERR_MEM, 1);
	set_command_array(token_list, &command_array, len_list);
	return (command_array);
}

char **get_envp(t_list *environ)
{
	char **envp;
	int len_list;
	int i;

	len_list = ft_lstsize(environ);
	envp = malloc(sizeof(char *) * (len_list + 1));
	if (envp == NULL)
		terminate(ERR_MEM, 1);
	i = 0;
	while (environ)
	{
		envp[i] = ft_strdup(((t_environ_content *)environ->content)->env_var);
		if (envp[i] == NULL)
			terminate(ERR_MEM, 1);
		i++;
		environ = environ->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	line_is_limitor(char *line, char *limitor)
{
	int	length_line;
	int	length_limitor;

	length_line = ft_strlen(line) - 1;
	length_limitor = ft_strlen(limitor);
	if (length_line >= length_limitor && ft_strncmp(line, limitor, length_line) == 0)
		return (1);
	else if (length_line < length_limitor && ft_strncmp(line, limitor, length_limitor) == 0)
		return (1);
	return (0);
}

void do_here_doc(int *fd_in, char *limitor)
{
	char	 *line;
	int		tmp_fd;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			printf("msh: warning: here-document delimited by end-of-file (wanted `%s')\n", limitor);
			break ;
		}
		if (line_is_limitor(line, limitor))
			break ;
		tmp_fd = open(TMP_FILE_HEREDOC, O_WRONLY | O_APPEND | O_CREAT, 0600);
		if (tmp_fd < 0)
			terminate(ERR_OPEN, 1);
		write(tmp_fd, line, ft_strlen(line));
		close(tmp_fd);
		free(line);
		line = NULL;
	}
	close(*fd_in);
	*fd_in = open(TMP_FILE_HEREDOC, O_RDONLY | O_CREAT);
	unlink(TMP_FILE_HEREDOC);
}

void dup_to_in(int fd_in, t_list *command)
{
	t_list			*token;
	t_token_content	*token_content;

	token = ((t_cmd_line_content *)command->content)->word;
	while (token)
	{
		token_content = token->content;
		if (token_content->type == OPEN_FILE)
		{
			close(fd_in);
			fd_in = open(token_content->word, O_RDONLY);
			if (fd_in < 0)
				terminate(ERR_OPEN, 1);
		}
		else if (token_content->type == LIMITOR)
			do_here_doc(&fd_in, token_content->word);
		token = token->next;
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
		terminate(ERR_DUP, 1);
}

void dup_to_out(int fd_out, t_list *command, int last)
{
	t_list *token;
	t_token_content *token_content;
	int did_redirection;

	did_redirection = 0;
	token = ((t_cmd_line_content *)command->content)->word;
	while (token)
	{
		token_content = token->content;
		if (token_content->type == EXIT_FILE)
		{
			close(fd_out);
			fd_out = open(token_content->word,
						  O_WRONLY | O_TRUNC | O_CREAT, 0644);
			did_redirection = 1;
		}
		else if (token_content->type == EXIT_FILE_APP)
		{
			close(fd_out);
			fd_out = open(token_content->word,
						  O_WRONLY | O_APPEND | O_CREAT, 0644);
			did_redirection = 1;
		}
		if (fd_out < 0)
			terminate(ERR_OPEN, 1);
		token = token->next;
	}
	if ((last == 0 || (last == 1 && did_redirection == 1)) && dup2(fd_out, STDOUT_FILENO) == -1)
		terminate(ERR_DUP, 1);
}
