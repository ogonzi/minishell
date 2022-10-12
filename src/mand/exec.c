/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:24:16 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/12 13:03:42 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		printf("%s\n", tokens[i]);
		i++;
	}
}

void	do_child(char ***tokens)
{
	char	*exec_path;

	set_child_sigaction();
	get_exec_path(tokens, &exec_path);
	if (execve(exec_path, *tokens, NULL) == -1)
		terminate(ERR_EXECVE, 1);
}

void	do_parent(void)
{
	int	child_exit_status;
	int	wstatus;

	do_sigign(SIGINT);
	if (wait(&wstatus) == -1)
		terminate(ERR_WAIT, 1);
	if (WIFEXITED(wstatus))
	{
		set_sigint_action();
		child_exit_status = WEXITSTATUS(wstatus);
		(void)child_exit_status;
	}
}

void	exec(char ***tokens)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		terminate(ERR_FORK, 1);
	else if (pid == 0)
		do_child(tokens);
	else
		do_parent();
}
