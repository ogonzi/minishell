/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:51:36 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/18 20:00:06 by ogonzale         ###   ########.fr       */
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

int	handle_input(t_list **cmd_line)
{
	char	*buf;
	int		len_buf;

	buf = readline("msh> ");
	if (buf == NULL)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		return (1);
	}
	len_buf = ft_strlen(buf);
	if (len_buf != 0)
	{
		add_history(buf);
		split_cmd_line(cmd_line, buf);
		free(buf);
		buf = NULL;
		return (0);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_list	*cmd_line;

	if (argc != 1)
		terminate(ERR_ARGS, 0);
	set_sigint_action();
	do_sigign(SIGQUIT);
	init_shell();
	cmd_line = NULL;
	while (1)
	{
		if (handle_input(&cmd_line) == 1)
			break ;
		free_cmd_line(cmd_line);
		cmd_line = NULL;
	}
	(void)argv;
	return (0);
}
