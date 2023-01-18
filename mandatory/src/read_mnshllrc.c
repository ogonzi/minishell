/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_mnshllrc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:19:37 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/01/18 16:00:53 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_utils.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PTHFLE  (char *)"./.mnshllrc"
#define ERRMSG  (char *)"Error while reading .mnshllrc file!\a\n"

static void	protect_line(char **line, int fd);

void	read_mnshllrc(void)
{
	int		fd;
	char	*line;

	fd = open(PTHFLE, O_RDONLY);
	if (fd < 0 || fd > OPEN_MAX)
	{
		ft_printf_fd(STDERR_FILENO, "%s", ERRMSG);
		return ;
	}
	while (42)
	{
		protect_line(&line, fd);
		if (!line)
			break ;
		while (ft_isspace(*line))
			line++;
		if (line[0] == '#')
			continue ;
		printf("%s", line);
	}
}

static void	protect_line(char **line, int fd)
{
	*line = get_next_line(fd);
	if (!*line)
	{
		free(*line);
		line = NULL;
		close(fd);
	}
}
