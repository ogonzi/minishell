/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:38:49 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/09 18:28:21 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

static int	do_pipe(int tmp_fd[2], t_list *command,
				t_prompt prompt, t_pipe pipe_helper);
static int	do_last_pipe_parent(int tmp_fd[2], t_pipe pipe_helper, pid_t pid);
static void	do_child(int tmp_fd[2], t_list *command,
				t_prompt prompt, t_pipe pipe_helper);

int	redir_pipe(t_list *command_cpy, t_prompt prompt, int tmp_fd[2])
{
	int		exit_status;
	t_pipe	pipe_helper;

	exit_status = dup_to_in(&tmp_fd[0], command_cpy);
	if (exit_status == 0)
		exit_status = dup_to_out(&tmp_fd[1], command_cpy,
				&pipe_helper.did_out_redirection);
	if (exit_status == 0 && command_cpy->next)
		pipe_helper.is_last = 0;
	else if (exit_status == 0)
		pipe_helper.is_last = 1;
	do_sigign(SIGINT);
	do_sigign(SIGQUIT);
	exit_status = do_pipe(tmp_fd, command_cpy, prompt, pipe_helper);
	return (exit_status);
}

static int	do_pipe(int tmp_fd[2], t_list *command,
				t_prompt prompt, t_pipe pipe_helper)
{
	pid_t	pid;

	if (pipe(pipe_helper.fd))
		exit(1); // terminate(ERR_PIPE, 1);
	pid = fork();
	if (pid < 0)
		exit(1); // terminate(ERR_FORK, 1);
	else if (pid > 0 && !pipe_helper.is_last)
	{
		if (dup2(pipe_helper.fd[0], tmp_fd[0]) == ERRNUM)
			exit(1); // terminate(ERR_DUP, 1);
		if (close(pipe_helper.fd[0]))
			exit(1); // terminate(ERR_CLOSE, 1);
		if (close(pipe_helper.fd[1]))
			exit(1); // terminate(ERR_CLOSE, 1);
	}
	else if (pid > 0 && pipe_helper.is_last == TRUE)
		return (do_last_pipe_parent(tmp_fd, pipe_helper, pid));
	else if (pid == 0)
		do_child(tmp_fd, command, prompt, pipe_helper);
	return (FALSE);
}

static int	do_last_pipe_parent(int tmp_fd[2], t_pipe pipe_helper, pid_t pid)
{
	int	last_pipe_exit;
	int	exit_status;

	if (close(pipe_helper.fd[0]))
		exit(1); // terminate(ERR_CLOSE, 1);
	if (dup2(pipe_helper.fd[1], tmp_fd[1]) == ERRNUM)
		exit(1); // terminate(ERR_DUP, 1);
	if (close(pipe_helper.fd[1]))
		exit(1); // terminate(ERR_CLOSE, 1);
	last_pipe_exit = FALSE;
	while (waitpid(pid, &exit_status, 0) != ERRNUM)
		;
	last_pipe_exit = handle_child_exit(exit_status, last_pipe_exit, 1);
	exit_status = 0;
	while (waitpid(WAIT_ANY, &exit_status, 0) != ERRNUM)
		;
	return (handle_child_exit(exit_status, last_pipe_exit, 0));
}

static void	do_child(int tmp_fd[2], t_list *command,
					t_prompt prompt, t_pipe pipe_helper)
{
	if (close(pipe_helper.fd[0]))
		exit(1); //terminate(ERR_CLOSE, 1);
	if (dup2(tmp_fd[0], STDIN_FILENO) == ERRNUM)
		exit(1); //terminate(ERR_DUP, 1);
	if (close(tmp_fd[0]))
		exit(1); //terminate(ERR_CLOSE, 1);
	do_execve(command, prompt, tmp_fd, pipe_helper);
}

void	do_execve(t_list *command, t_prompt prompt,
					int tmp_fd[2], t_pipe pipe_helper)
{
	char	**envp;
	char	**command_array;
	char	*exec_path;

	envp = copy_env(prompt.env, ft_env_size(prompt.env));
	command_array = get_command_array(command);
	if (get_exec_path(command_array[0], &exec_path, command, &prompt))
	{
		printf("%s: command not found\n", command_array[0]);
		exit(((t_cmdline *)command->data)->exit_status);
	}
	check_pipe(&pipe_helper, tmp_fd);
	set_child_sigaction();
	// printf("%s", command_array[1]);
	if (!ft_strcmp(ft_strlowcase(command_array[0]), "pwd"))
	{
		((t_cmdline *)command->data)->exit_status = printf("this should be the pwd\n");
		exit(((t_cmdline *)command->data)->exit_status);
	}
	if (execve(exec_path, command_array, envp) == -1)
		exit(1); // terminate(ERR_EXECVE, 1);
}
