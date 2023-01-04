/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:24:16 by ogonzale          #+#    #+#             */
/*   Updated: 2023/01/04 19:53:24 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"

//TODO: Change handling of error message if get_exec_path returns != 0 -> print to STDERR
static void	do_execve(t_list *command, t_prompt prompt, int fd[2], int tmp_fd[2], int did_out_redirection)
{
	char	*exec_path;
	char	**command_array;
	char	**envp;
	int		is_last;

	if (command->next == NULL)
		is_last = 1;
	else
		is_last = 0;
	set_child_sigaction();
	command_array = get_command_array(command);
	envp = get_envp(prompt.environ);
	if (get_exec_path(command_array[0], &exec_path, command, &prompt) != 0)
	{
		printf("%s: command not found\n", command_array[0]);
		exit(((t_cmd_line_content *)command->content)->exit_status);
	}
	if (did_out_redirection == 0 && is_last == 0 && dup2(fd[1], STDOUT_FILENO) == -1)
		terminate(ERR_DUP, 1);
	else if (did_out_redirection == 1 && dup2(tmp_fd[1], STDOUT_FILENO) == -1)
		terminate(ERR_DUP, 1);
	if (close(fd[1]) != 0)
		terminate(ERR_CLOSE, 1);
	if (close(tmp_fd[1]) != 0)
		terminate(ERR_CLOSE, 1);
	if (execve(exec_path, command_array, envp) == -1)
		terminate(ERR_EXECVE, 1);
}

static void	do_child(int fd[2], int tmp_fd[2], t_list *command, t_prompt prompt, int did_out_redirection)
{
	if (close(fd[0]) != 0)
		terminate(ERR_CLOSE, 1);
	if (dup2(tmp_fd[0], STDIN_FILENO) == -1)
		terminate(ERR_DUP, 1);
	if (close(tmp_fd[0]) != 0)
		terminate(ERR_CLOSE, 1);
	do_execve(command, prompt, fd, tmp_fd, did_out_redirection);
}

static void	do_pipe(int fd[2], int tmp_fd[2], t_list *command, t_prompt prompt, int did_out_redirection)
{
	pid_t	pid;

	if (pipe(fd) != 0)
		terminate(ERR_PIPE, 1);
	pid = fork();
	if (pid < 0)
		terminate(ERR_FORK, 1);
	else if (pid > 0)
	{
		if (dup2(fd[0], tmp_fd[0]) == -1)
			terminate(ERR_DUP, 1);
		if (close(fd[0]) != 0)
			terminate(ERR_CLOSE, 1);
		if (close(fd[1]) != 0)
			terminate(ERR_CLOSE, 1);
	}
	else if (pid == 0)
		do_child(fd, tmp_fd, command, prompt, did_out_redirection);
}

static int
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
			write(STDOUT_FILENO, "\n", 1);
			if (last_pipe == 1 || (last_pipe == 0 && last_pipe_exit != 0))
				return (130);
		}
		if (WTERMSIG(exit_status) == SIGQUIT)
		{
			write(STDOUT_FILENO, "Quit\n", 5);
			rl_on_new_line();
			if (last_pipe == 1 || (last_pipe == 0 && last_pipe_exit != 0))
				return (131);
		}
	}
	return (last_pipe_exit);
}

static int	do_last_command(int fd[2], int tmp_fd[2],
							t_list *command, t_prompt prompt, int did_out_redirection)
{
	pid_t	pid;
	int		exit_status;
	int		last_pipe_exit;

	if (pipe(fd) != 0)
		terminate(ERR_PIPE, 1);
	pid = fork();
	if (pid < 0)
		terminate(ERR_FORK, 1);
	else if (pid > 0)
	{
		if (close(fd[0]) != 0)
			terminate(ERR_CLOSE, 1);
		if (dup2(fd[1], tmp_fd[1]) == -1)
			terminate(ERR_DUP, 1);
		if (close(fd[1]) != 0)
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
	else if (pid == 0)
		do_child(fd, tmp_fd, command, prompt, did_out_redirection);
	return (0);
}

int	redir_pipe(t_list *command_cpy, t_prompt prompt, int tmp_fd[2])
{
	int	fd[2];
	int	exit_status;
	int	did_out_redirection;

	do_sigign(SIGINT);
	do_sigign(SIGQUIT);
	exit_status = dup_to_in(&tmp_fd[0], command_cpy);
	if (exit_status == 0)
		exit_status = dup_to_out(&tmp_fd[1], command_cpy, &did_out_redirection);
	if (exit_status == 0 && command_cpy->next)
		do_pipe(fd, tmp_fd, command_cpy, prompt, did_out_redirection);
	else if (exit_status == 0)
		exit_status = do_last_command(fd, tmp_fd, command_cpy, prompt, did_out_redirection);
	return (exit_status);
}
