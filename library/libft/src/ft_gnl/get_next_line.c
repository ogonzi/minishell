/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:35:34 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/05/01 17:25:05 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_and_save(int fd, char *buffer);
static char	*get_line(char **buffer);
static void	*clean_buffer(void **dlt);

char
	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = ft_strdup("");
		if (!buffer[fd])
			return (clean_buffer((void **)&buffer[fd]));
	}
	buffer[fd] = read_and_save(fd, buffer[fd]);
	if (!buffer[fd] || buffer[fd][0] == '\0')
		return (clean_buffer((void **)&buffer[fd]));
	return (get_line(&buffer[fd]));
}

static char
	*read_and_save(int fd, char *buffer)
{
	char	*line;
	int		bytes;

	line = ft_calloc((BUFFER_SIZE + 2), sizeof(char));
	if (!line)
		return (clean_buffer((void **)&buffer));
	bytes = 1;
	while (bytes && !ft_strchr(buffer, '\n'))
	{
		bytes = read(fd, line, BUFFER_SIZE);
		if (bytes == -1)
		{
			clean_buffer((void **)&line);
			return (clean_buffer((void **)&buffer));
		}
		line[bytes] = '\0';
		buffer = ft_memjoin(buffer, line);
		if (!buffer)
			return (clean_buffer((void **)&line));
	}
	clean_buffer((void **)&line);
	if (buffer)
		return (buffer);
	return (NULL);
}

static char
	*get_line(char **buffer)
{
	int		i;
	char	*line;
	char	*tmp;

	i = 0;
	while ((*buffer)[i] != '\n' && (*buffer)[i])
		i++;
	line = ft_substr(*buffer, 0, i + 1);
	if (!line)
		return (NULL);
	if ((*buffer)[i] == '\n')
	{
		tmp = ft_substr(*buffer, i + 1, ft_strlen(*buffer) - i);
		if (!tmp)
			return (clean_buffer((void **)&line));
	}
	else
	{
		tmp = ft_calloc(1, sizeof(char));
		if (!tmp)
			return (clean_buffer((void **)&line));
	}
	clean_buffer((void **)&(*buffer));
	*buffer = tmp;
	return (line);
}

static void
	*clean_buffer(void **dlt)
{
	free(*dlt);
	*dlt = NULL;
	return (NULL);
}
