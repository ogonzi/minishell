/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:51:36 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/10 21:00:10 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void	handler(int signum)
{
	//rl_replace_line("", 0);
	(void)signum;
}

void	fork_process(char **line)
{
	pid_t				pid;
//	struct sigaction	sa;
	int					child_exit_status;
	int					wstatus;

	pid = fork();
	if (pid < 0)
		terminate(ERR_FORK, 1);
	else if (pid == 0)
	{
//		sa.sa_handler = &handler;
//		sa.sa_flags = SA_RESTART;
//		if (sigaction(SIGINT, &sa, 0) == -1)
//			terminate(ERR_SIG, 1);
		signal(SIGINT, SIG_DFL);
		sleep(5);
		if (*line)
			printf("%s\n", *line);
		exit(0);
	}
	else
	{
		if (wait(&wstatus) == -1)
			terminate(ERR_WAIT, 1);
		if (WIFEXITED(wstatus))
		{
			child_exit_status = WEXITSTATUS(wstatus);
			printf("child exit status = %d\n", child_exit_status);
		}
		if (WIFSIGNALED(wstatus))
		{
			if (WTERMSIG(wstatus) == SIGINT)
				printf("Child terminated with sigint\n");
		}
	}

}

int	handle_input(char **line)
{
	char	*buf;
	int		len_buf;

	buf = readline("msh> ");
	if (buf == NULL)
	{
		printf("exit\n");
		return (1);
	}
	len_buf = ft_strlen(buf);
	if (len_buf != 0)
	{
		add_history(buf);
		*line = malloc(sizeof(char) * (len_buf + 1));
		if (*line == NULL)
			terminate(ERR_MEM, 1);
		ft_strlcpy(*line, buf, len_buf + 1);
		free(buf);
		buf = NULL;
		fork_process(line);
		free(*line);
		return (0);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	char				*line;

	if (argc != 1)
		terminate(ERR_ARGS, 0);
	handle_signals();
	init_shell();
	while (1)
	{
		if (handle_input(&line) == 1)
			break ;
	}
	(void)argv;
	return (0);
}
