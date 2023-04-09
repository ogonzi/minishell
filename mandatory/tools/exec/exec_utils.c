/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 12:57:21 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/09 13:32:40 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

static void	set_command_array(t_list *token_list, char ***command_array,
				size_t len_list);

int	handle_child_exit(int exit_status, int last_pipe_exit, int last_pipe)
{
	if (WIFEXITED(exit_status) && last_pipe == TRUE)
		return (WEXITSTATUS(exit_status));
	if (WIFSIGNALED(exit_status))
	{
		if (WCOREDUMP(exit_status))
			exit(1); // terminate(ERR_CHLD, 0);
		if (WTERMSIG(exit_status) == SIGINT)
		{
			if (last_pipe == TRUE)
				ft_printf_fd(STDOUT_FILENO, "\n");
			if (last_pipe == TRUE
				|| (last_pipe == FALSE && last_pipe_exit != 0))
				return (TERMINATE_CTRL_C);
		}
		if (WTERMSIG(exit_status) == SIGQUIT)
		{
			if (last_pipe == TRUE)
				exit(1); // write(STDOUT_FILENO, "Quit\n", 5);
			rl_on_new_line();
			if (last_pipe == TRUE
				|| (last_pipe == FALSE && last_pipe_exit != 0))
				return (TERMINATE_QUIT);
		}
	}
	return (last_pipe_exit);
}

void	check_pipe(t_pipe *pipe_helper, int tmp_fd[2])
/*
 * In summary, this function sets up the output redirection and piping for a
 * command in a shell program. The function takes two arguments, a t_pipe struct
 * named pipe_helper and an array of integers named tmp_fd representing file descriptors.

 * First, the function checks if the current command did not have output redirection,
 * is not the last command in the pipeline, and duplicates the write-end of the pipe
 * to the standard output file descriptor (STDOUT_FILENO). If the dup2() function fails
 * to duplicate the file descriptor, the program terminates with an error.

 * If the current command did have output redirection, the function duplicates the
 * write-end of the temporary file descriptor array tmp_fd to the standard output
 * file descriptor.

 * Then, the function closes the write-end of the pipe and the temporary file
 * descriptor array. If the close() function fails to close any of these file descriptors,
 * the program terminates with an error.
*/
{
	if (pipe_helper->did_out_redirection == 0 && pipe_helper->is_last == 0
		&& dup2(pipe_helper->fd[1], STDOUT_FILENO) == -1)
		terminate(ERR_DUP, 1);
	else if (pipe_helper->did_out_redirection == 1
		&& dup2(tmp_fd[1], STDOUT_FILENO) == -1)
		terminate(ERR_DUP, 1);
	if (close(pipe_helper->fd[1]) != 0)
		terminate(ERR_CLOSE, 1);
	if (close(tmp_fd[1]) != 0)
		terminate(ERR_CLOSE, 1);
}

char	**copy_env(t_env *env, size_t size)
{
	char	**env_cpy;
	t_env	*cpy;
	ssize_t	idx;

	env_cpy = ft_calloc(sizeof(char *), size);
	if (!env_cpy)
		exit(1); // terminate(ERR_MEM, 1);
	cpy = env;
	idx = 0;
	while (cpy)
	{
		env_cpy[idx] = ft_strdup(ft_strjoin(ft_strjoin(cpy->env_var, "="),
					cpy->env_data));
		if (!env_cpy)
			exit(1); // terminate(ERR_MEM, 1);
		++idx;
		cpy = cpy->next;
	}
	return (env_cpy);
}

char	**get_command_array(t_list *command)
{
	char	**command_array;
	t_list	*token_list;
	size_t	len_list;

	token_list = ((t_cmdline *)command->data)->word;
	len_list = ft_lstsize(token_list);
	command_array = malloc(sizeof(char *) * (len_list + 1));
	if (!command_array)
		exit(1); // terminate(ERR_MEM, 1);
	set_command_array(token_list, &command_array, len_list);
	return (command_array);
}

static void	set_command_array(t_list *token_list, char ***command_array,
				size_t len_list)
{
	size_t	idx;

	idx = 0;
	while (token_list)
	{
		if (((t_token *)token_list->data)->type == 1)
		{
			(*command_array)[idx]
				= ft_strdup(((t_token *)token_list->data)->word);
			if (!(*command_array)[idx])
				exit(1); // terminate(ERR_MEM, 1);
			++idx;
		}
		token_list = token_list->next;
	}
	while (idx <= len_list)
	{
		(*command_array)[idx] = NULL;
		idx++;
	}
}
