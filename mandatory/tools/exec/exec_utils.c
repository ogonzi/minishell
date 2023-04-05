/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:09:09 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/05 01:35:33 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_utils.h"

static void	set_command_array(t_list *token_list, char ***command_array,
								int len_list)
{
	int	i;

	i = 0;
	while (token_list)
	{
		if (((t_token_data *)token_list->data)->type == 1)
		{
			(*command_array)[i]
				= ft_strdup(((t_token_data *)token_list->data)->word);
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

char	**get_command_array(t_list *command)
{
	char	**command_array;
	t_list	*token_list;
	int		len_list;

	token_list = ((t_cmd_line_data *)command->data)->word;
	len_list = ft_lstsize(token_list);
	command_array = malloc(sizeof(char *) * (len_list + 1));
	if (command_array == NULL)
		terminate(ERR_MEM, 1);
	set_command_array(token_list, &command_array, len_list);
	return (command_array);
}

char	**get_envp(t_list *environ)
{
	char	**envp;
	int		len_list;
	int		i;

	len_list = ft_lstsize(environ);
	envp = malloc(sizeof(char *) * (len_list + 1));
	if (envp == NULL)
		terminate(ERR_MEM, 1);
	i = 0;
	while (environ)
	{
		envp[i] = ft_strdup(((t_environ_data *)environ->data)->env_var);
		if (envp[i] == NULL)
			terminate(ERR_MEM, 1);
		i++;
		environ = environ->next;
	}
	envp[i] = NULL;
	return (envp);
}

int
	handle_child_exit(int exit_status, int last_pipe_exit, int last_pipe)
{
	if (WIFEXITED(exit_status) && last_pipe == 1)
		return (WEXITSTATUS(exit_status));
	if (WIFSIGNALED(exit_status))
	{
		if (WCOREDUMP(exit_status))
			terminate(ERR_CHLD, 0);
		if (WTERMSIG(exit_status) == SIGINT)
		{
			if (last_pipe == 1)
				write(STDOUT_FILENO, "\n", 1);
			if (last_pipe == 1 || (last_pipe == 0 && last_pipe_exit != 0))
				return (TERMINATE_CTRL_C);
		}
		if (WTERMSIG(exit_status) == SIGQUIT)
		{
			if (last_pipe == 1)
				write(STDOUT_FILENO, "Quit\n", 5);
			rl_on_new_line();
			if (last_pipe == 1 || (last_pipe == 0 && last_pipe_exit != 0))
				return (TERMINATE_QUIT);
		}
	}
	return (last_pipe_exit);
}

void	check_pipe(t_pipe *pipe_helper, int tmp_fd[2])
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
