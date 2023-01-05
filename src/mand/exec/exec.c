/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:24:16 by ogonzale          #+#    #+#             */
/*   Updated: 2023/01/05 18:52:39 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"

//TODO: Use modded ft_printf to print errors to STDERR
static void	do_execve(t_list *command, t_prompt prompt,
						int tmp_fd[2], t_pipe pipe_helper)
{
	char	*exec_path;
	char	**command_array;
	char	**envp;

	set_child_sigaction();
	command_array = get_command_array(command);
	envp = get_envp(prompt.environ);
	if (get_exec_path(command_array[0], &exec_path, command, &prompt) != 0)
	{
		printf("%s: command not found\n", command_array[0]);
		exit(((t_cmd_line_content *)command->content)->exit_status);
	}
	if (pipe_helper.did_out_redirection == 0 && pipe_helper.is_last == 0
		&& dup2(pipe_helper.fd[1], STDOUT_FILENO) == -1)
		terminate(ERR_DUP, 1);
	else if (pipe_helper.did_out_redirection == 1
		&& dup2(tmp_fd[1], STDOUT_FILENO) == -1)
		terminate(ERR_DUP, 1);
	if (close(pipe_helper.fd[1]) != 0)
		terminate(ERR_CLOSE, 1);
	if (close(tmp_fd[1]) != 0)
		terminate(ERR_CLOSE, 1);
	if (execve(exec_path, command_array, envp) == -1)
		terminate(ERR_EXECVE, 1);
}

static void	do_child(int tmp_fd[2], t_list *command,
					t_prompt prompt, t_pipe pipe_helper)
{
	if (close(pipe_helper.fd[0]) != 0)
		terminate(ERR_CLOSE, 1);
	if (dup2(tmp_fd[0], STDIN_FILENO) == -1)
		terminate(ERR_DUP, 1);
	if (close(tmp_fd[0]) != 0)
		terminate(ERR_CLOSE, 1);
	do_execve(command, prompt, tmp_fd, pipe_helper);
}

static int	do_last_pipe_parent(int tmp_fd[2], t_pipe pipe_helper, pid_t pid)
{
	int	last_pipe_exit;
	int	exit_status;

	if (close(pipe_helper.fd[0]) != 0)
		terminate(ERR_CLOSE, 1);
	if (dup2(pipe_helper.fd[1], tmp_fd[1]) == -1)
		terminate(ERR_DUP, 1);
	if (close(pipe_helper.fd[1]) != 0)
		terminate(ERR_CLOSE, 1);
	last_pipe_exit = 0;
	while (waitpid(pid, &exit_status, 0) != -1)
		;
	last_pipe_exit = handle_child_exit(exit_status, last_pipe_exit, 1);
	exit_status = 0;
	while (waitpid(WAIT_ANY, &exit_status, 0) != -1)
		;
	return (handle_child_exit(exit_status, last_pipe_exit, 0));
}

static int	do_pipe(int tmp_fd[2], t_list *command,
					t_prompt prompt, t_pipe pipe_helper)
{
	pid_t	pid;

	if (pipe(pipe_helper.fd) != 0)
		terminate(ERR_PIPE, 1);
	pid = fork();
	if (pid < 0)
		terminate(ERR_FORK, 1);
	else if (pid > 0 && pipe_helper.is_last == 0)
	{
		if (dup2(pipe_helper.fd[0], tmp_fd[0]) == -1)
			terminate(ERR_DUP, 1);
		if (close(pipe_helper.fd[0]) != 0)
			terminate(ERR_CLOSE, 1);
		if (close(pipe_helper.fd[1]) != 0)
			terminate(ERR_CLOSE, 1);
	}
	else if (pid > 0 && pipe_helper.is_last == 1)
		return (do_last_pipe_parent(tmp_fd, pipe_helper, pid));
	else if (pid == 0)
		do_child(tmp_fd, command, prompt, pipe_helper);
	return (0);
}

int	redir_pipe(t_list *command_cpy, t_prompt prompt, int tmp_fd[2])
{
	int		exit_status;
	t_pipe	pipe_helper;	

	do_sigign(SIGINT);
	do_sigign(SIGQUIT);
	exit_status = dup_to_in(&tmp_fd[0], command_cpy);
	if (exit_status == 0)
		exit_status = dup_to_out(&tmp_fd[1], command_cpy,
				&pipe_helper.did_out_redirection);
	if (exit_status == 0 && command_cpy->next)
		pipe_helper.is_last = 0;
	else if (exit_status == 0)
		pipe_helper.is_last = 1;
	exit_status = do_pipe(tmp_fd, command_cpy, prompt, pipe_helper);
	return (exit_status);
}
