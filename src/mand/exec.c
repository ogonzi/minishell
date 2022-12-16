/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:24:16 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/16 09:22:46 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"

static char **get_command_array(t_list *command)
{
	char	**command_array;
	t_list	*token_list;
	int		len_list;
	int		i;

	token_list = ((t_cmd_line_content *)command->content)->word;
	len_list = ft_lstsize(token_list);
	command_array = malloc(sizeof(char *) * (len_list + 1));
	if (command_array == NULL)
		terminate(ERR_MEM, 1);
	i = 0;
	while (token_list)
	{
		if (((t_token_content *)token_list->content)->type == 1)
		{
			command_array[i] = ft_strdup(((t_token_content *)token_list->content)->word);
			if (command_array[i] == NULL)
				terminate(ERR_MEM, 1);
			i++;
		}
		token_list = token_list->next;
	}
	while (i < len_list + 1)
	{
		command_array[i] = NULL;
		i++;
	}
	return (command_array);
}

static void	do_pipe(int fd[2], int *tmp_fd, t_list *command, t_prompt prompt)
{
	pid_t 	pid;
	//char	*infile;
	//char	*outfile;
	char	**command_array;
	char	*exec_path;

	pipe(fd);
	pid = fork();
	if (pid)
	{
		close(fd[1]);
		close(*tmp_fd);
		*tmp_fd = fd[0];
	}
	else if (!pid)
	{
		command_array = get_command_array(command);
		if (get_exec_path(command_array[0], &exec_path, command, &prompt) != 0)
			exit(((t_cmd_line_content *)command->content)->exit_status);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(*tmp_fd, STDIN_FILENO);
		close(*tmp_fd);
		execve(exec_path, command_array, 0);
		write(STDERR_FILENO, "Error\n", 6);
	}
	(void)prompt;
}

static void do_last_command(int *tmp_fd, t_list *command, t_prompt prompt)
{
	pid_t 	pid;
	char	*exec_path;
	char	**command_array;

	pid = fork();
	if (pid)
	{
		close(*tmp_fd);
		while (waitpid(-1, NULL, WUNTRACED) != -1)
			;
		*tmp_fd = dup(STDIN_FILENO);
	}
	else if (!pid)
	{
		command_array = get_command_array(command);
		if (get_exec_path(command_array[0], &exec_path, command, &prompt) != 0)
			exit(((t_cmd_line_content *)command->content)->exit_status);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(*tmp_fd, STDIN_FILENO);
		close(*tmp_fd);
		execve(exec_path, command_array, 0);
		write(STDERR_FILENO, "Error\n", 6);
	}
}

void redir_pipe(t_list *command_cpy, t_prompt prompt, int *tmp_fd)
{
	int fd[2];

	do_sigign(SIGINT);
	do_sigign(SIGQUIT);
	if (command_cpy->next)
		do_pipe(fd, tmp_fd, command_cpy, prompt);
	else
		do_last_command(tmp_fd, command_cpy, prompt);
}
