/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:24:16 by ogonzale          #+#    #+#             */
/*   Updated: 2023/01/06 10:26:26 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"

//TODO: Use modded ft_printf to print errors to STDERR
//TODO: Handle execve error (free mem, error message)
/**
 * First, the array of commands for the pipe is obtained. For example,
 * "echo -n hello" -> [echo, -n, hello]. Then, the array of environment
 * variables is obtained. Both get_command_array and get_envp transform
 * a linked list into a 2D array. Then, the executable path is obtained.
 * If it doesn't exist, the user doesn't have permissions, etc. a message
 * is printed and an error code is returned.
 * Then, the corresponding ouput redirections are performed:
 * if an output redirection was performed, tmp_fd[1] is dupped to 
 * stdout. If no redirection was performed and the pipe isn't the
 * last one, fd[1] is dupped to stdout. Both are closed and a
 * call to execve is performed, previously defining the sigactions
 * that it should follow.
*/
static void	do_execve(t_list *command, t_prompt prompt,
						int tmp_fd[2], t_pipe pipe_helper)
{
	char	*exec_path;
	char	**command_array;
	char	**envp;

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
	set_child_sigaction();
	if (execve(exec_path, command_array, envp) == -1)
		terminate(ERR_EXECVE, 1);
}

/**
 * Closes the read end of the pipe, duplicates tmp_fd[0] to the
 * standard input, and closes tmp_fd[0]. This sequences gets the
 * input for the pipe from either STDIN or a file/heredoc if
 * redirection was present and tmp_fd[0] was dupped to it. Then, 
 * do_execve is called.
*/
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

/**
 * Closes the read end of the pipe and duplicates the write end (fd[1]) to
 * tmp_fd[1], then closes fd[1]. Then waits for the current process to end
 * (the last pipe). It then captures the exit code for the last pipe in
 * last_pipe_exit and waits for other pipes to end, returning the exit_code
 * of the last pipe.
*/
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

/**
 * Creates pipe and forks process. In the parent, for pipes which
 * aren't last, duplicates the read end of the pipe (fd[0]) to tmp_fd[0],
 * which could be STDIN or a file/heredoc. Then closes both ends of the pipe.
 * For the last pipe, returns 0 or error code. In the child, do_child is
 * called.
*/
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

/**
 * dup_to_in and dup_to_out check and implement redirections, capturing an
 * error code if necessary. SIGINT and SIGQUIT are ignored so as to not 
 * capture signals twice. do_pipe is called, which acts diferent for the
 * last pipe. Returns the exit status of the current pipe (0 for any pipe
 * that isn't last, 0 or error code for last pipe) 
*/
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
