/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:51:36 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/06 20:11:18 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void	init_shell(void)
{
	printf("\n\n\n\n*******************************");
	printf("\n\n**PROVISIONAL MINISHELL START**");
	printf("\n\n*******************************");
	printf("\n\nUser is: %s\n", getenv("USER"));
	printf("\n");
}

/*
 * En principi el limit de longitud d'un path en MAC es 1024, hi ha una
 * constant que es diu PATH_MAX que ho hauria d'especificar, pero caldria
 * utilizar limits.h i el mateix getcwd diu que no es gaire bona idea
 * utilitzar-ho.
 */

void	print_dir(void)
{
	char	buf[1024];
	char	*err;

	err = getcwd(buf, sizeof(buf));
	if (err == NULL)
		terminate(ERR_GETPWD, 1);
	printf("\033[0;32m");
	printf("%s@%s", getenv("USER"), getenv("NAME"));
	printf("\033[0m");
	printf(":");
	printf("\033[0;34m");
	printf("%s", buf);
	printf("\033[0m");
}

int	handle_input(char **line)
{
	char	*buf;
	int		len_buf;

	buf = readline("$ ");
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
		printf("Input: %s\n", *line);
		free(*line);
		return (0);
	}
	return (0);
}

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		print_dir();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char *argv[])
{
	char				*line;
	struct sigaction	sa;

	if (argc != 1)
		terminate(ERR_ARGS, 0);
	sa.sa_handler = &handle_sig;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		terminate(ERR_SIG, 1);
	init_shell();
	while (1)
	{
		print_dir();
		if (handle_input(&line) == 1)
			break ;
	}
	(void)argv;
	return (0);
}
