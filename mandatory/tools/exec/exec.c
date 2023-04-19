/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:38:49 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/19 19:42:11 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_exec.h"
#include "mnshll_builtins.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

static int	do_pipe(int tmp_fd[2], t_list *command,
				t_prompt *prompt, t_pipe pipe_helper);
static int	do_last_pipe_parent(int tmp_fd[2], t_pipe pipe_helper, pid_t pid);
static void	do_child(int tmp_fd[2], t_list *command,
				t_prompt *prompt, t_pipe pipe_helper);

int	redir_pipe(t_list *command_cpy, t_prompt *prompt,
		int tmp_fd[2], int is_first)
{
	char	**command_array;
	char	**envp;
	int		exit_status;
	t_pipe	pipe_helper;

	pipe_helper.is_first = is_first;
	exit_status = dup_to_in(&tmp_fd[0], command_cpy);
	if (exit_status == 0)
		exit_status = dup_to_out(&tmp_fd[1], command_cpy,
				&pipe_helper.did_out_redirection);
	if (exit_status == 0 && command_cpy->next)
		pipe_helper.is_last = FALSE;
	else if (exit_status == 0)
		pipe_helper.is_last = TRUE;
	do_sigign(SIGINT);
	do_sigign(SIGQUIT);
	if (pipe_helper.is_first && pipe_helper.is_last)
	{
		command_array = get_command_array(command_cpy);
		envp = copy_env(prompt->env, ft_env_size(prompt->env));
		check_ft_builtins2(prompt, pipe_helper, command_array, envp);
		aux_clean_cmd_env(&command_array, &envp);
	}
	exit_status = do_pipe(tmp_fd, command_cpy, prompt, pipe_helper);
	return (exit_status);
}

static int	do_pipe(int tmp_fd[2], t_list *command,
				t_prompt *prompt, t_pipe pipe_helper)
/*
 * First, the function creates a pipe using the pipe() system call and stores
 * the read and write file descriptors in pipe_helper.fd.

 * Next, it forks a child process using the fork() system call.
 * If the child process is created successfully, it will execute the do_child()
 * function, which sets up the necessary file descriptors and executes the
 * command using the do_execve() function.

 * If the parent process is created successfully and this is not the last pipe
 * in the sequence, it will set up the necessary file descriptors and close any
 * unnecessary file descriptors for the parent process using dup2() and close().

 * If the parent process is created successfully and this is the last pipe in
 * the sequence, it will return the result of the do_last_pipe_parent()
 * function.

 * If do_pipe() is successful, it will return FALSE.
*/
{
	pid_t	pid;

	if (pipe(pipe_helper.fd))
		ft_prompt_clear(prompt, ERR_PIPE, EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		ft_prompt_clear(prompt, ERR_FORK, EXIT_FAILURE);
	else if (pid > 0 && !pipe_helper.is_last)
	{
		if (dup2(pipe_helper.fd[0], tmp_fd[0]) == ERRNUM)
			ft_prompt_clear(prompt, ERR_DUP, EXIT_FAILURE);
		if (close(pipe_helper.fd[0]))
			ft_prompt_clear(prompt, ERR_CLOSE, EXIT_FAILURE);
		if (close(pipe_helper.fd[1]))
			ft_prompt_clear(prompt, ERR_CLOSE, EXIT_FAILURE);
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

	if (close(pipe_helper.fd[1]) != 0)
		terminate(ERR_CLOSE, 1);
	if (dup2(pipe_helper.fd[0], tmp_fd[0]) == ERRNUM)
		terminate(ERR_DUP, 1);
	if (close(pipe_helper.fd[0]) != 0)
		terminate(ERR_CLOSE, 1);
	last_pipe_exit = 0;
	while (waitpid(pid, &exit_status, 0) != ERRNUM)
		;
	last_pipe_exit = handle_child_exit(exit_status, last_pipe_exit, 1);
	exit_status = 0;
	while (waitpid(WAIT_ANY, &exit_status, WNOHANG) != ERRNUM)
		;
	return (handle_child_exit(exit_status, last_pipe_exit, 0));
}

static void	do_child(int tmp_fd[2], t_list *command,
					t_prompt *prompt, t_pipe pipe_helper)
/*
 * The function is responsible for performing several operations on file
 * descriptors and then executing the command using do_execve().

 * First, the function closes the read end of the pipe using 
 * close(pipe_helper.fd[0]). Next, it duplicates the read end of the temporary
 * pipe tmp_fd[0] to the standard input file descriptor (STDIN_FILENO) using
 * dup2(tmp_fd[0], STDIN_FILENO). Then, it closes the read end of the temporary
 * pipe using close(tmp_fd[0]).

 * Finally, it calls the do_execve() function to execute the command in the
 * child process.
*/
{
	if (close(pipe_helper.fd[0]))
		terminate(ERR_CLOSE, EXIT_FAILURE);
	if (dup2(tmp_fd[0], STDIN_FILENO) == ERRNUM)
		terminate(ERR_DUP, EXIT_FAILURE);
	if (close(tmp_fd[0]))
		terminate(ERR_CLOSE, EXIT_FAILURE);
	do_execve(command, prompt, tmp_fd, pipe_helper);
}

void	do_execve(t_list *command, t_prompt *prompt,
					int tmp_fd[2], t_pipe pipe_helper)
/*
 * The function then checks if there is a pipe involved in the command using
 * the check_pipe function. If there is, it sets up the appropriate file
 * descriptors using the tmp_fd array.

 * The function sets up a signal handler for the child process using the
 * set_child_sigaction function.

 * Finally, the function executes the command using the execve system call,
 * passing in the full path of the executable, the array of arguments, and
 * the environment variables. 
*/
{
	char	**envp;
	char	**command_array;
	char	*exec_path;
	int		exit_value;

	command_array = get_command_array(command);
	envp = copy_env(prompt->env, ft_env_size(prompt->env));
	check_pipe(&pipe_helper, tmp_fd);
	exit_value = check_ft_builtins1(prompt, command_array, envp);
	if (exit_value == -1)
	{
		if (!ft_env_iter(prompt->env, "PATH")
			|| (command_array[0][0] == '/' && !command_array[0][1]))
			cmd_not_found(command_array[0]);
		if (get_exec_path(command_array[0], &exec_path, command, prompt))
		{
			cmd_not_found(command_array[0]);
			exit(((t_cmdline *)command->data)->exit_status);
		}
		set_child_sigaction();
		if (execve(exec_path, command_array, envp) == ERRNUM)
			ft_prompt_clear(prompt, ERR_EXECVE, EXIT_FAILURE);
	}
	aux_clean_cmd_env(&command_array, &envp);
	exit(exit_value);
}
