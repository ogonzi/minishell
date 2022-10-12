/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:51:36 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/12 13:05:36 by ogonzale         ###   ########.fr       */
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

int	handle_input(char **line)
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
		*line = malloc(sizeof(char) * (len_buf + 1));
		if (*line == NULL)
			terminate(ERR_MEM, 1);
		ft_strlcpy(*line, buf, len_buf + 1);
		free(buf);
		buf = NULL;
		return (0);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	char	*line;
	char	**tokens;

	if (argc != 1)
		terminate(ERR_ARGS, 0);
	set_sigint_action();
	do_sigign(SIGQUIT);
	init_shell();
	while (1)
	{
		if (handle_input(&line) == 1)
			break ;
		tokens = ft_split_mod(line, " \f\n\r\t\v");
		free(line);
		if (tokens[0] != NULL)
			exec(&tokens);
		free(tokens);
	}
	(void)argv;
	return (0);
}
