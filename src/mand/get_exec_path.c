/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:39:10 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/19 12:14:38 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "minishell.h"
#include <stdio.h>

void	ft_get_paths(char ***paths, char *path_line)
{
	*paths = ft_split(path_line, ':');
	if (!(*paths))
		terminate(ERR_MEM, 1);
}

int	ft_check_access(char **exec_path, char **paths)
{
	if (access(*exec_path, X_OK) == 0)
	{
		if (*paths != NULL)
			ft_free_twod_memory(paths);
		return (1);
	}
	return (0);
}

int	ft_check_script(char **exec_path, char *first_arg, char **paths)
{
	*exec_path = ft_strdup(first_arg);
	if (!(*exec_path))
		terminate(ERR_MEM, 1);
	if (ft_check_access(exec_path, paths) == 1)
	{
		if (ft_strchr((const char *)*exec_path, '/') == NULL)
			exit(127);
		return (1);
	}
	return (0);
}

void	ft_get_full_path(char *path, char **full_path, char *user_exec_path,
			char **exec_path)
{
	*full_path = ft_strjoin(path, "/");
	if (!(*full_path))
		terminate(ERR_MEM, 1);
	*exec_path = ft_strjoin(*full_path, user_exec_path);
	if (!(*exec_path))
		terminate(ERR_MEM, 1);
	free(*full_path);
}

int	get_exec_path(char ***tokens, char **exec_path)
{
	char	**paths;
	char	*path_line;
	char	*full_path;
	int		i;

	path_line = getenv("PATH");
	paths = NULL;
	if (path_line != NULL)
	{
		ft_get_paths(&paths, path_line);
		i = 0;
		while (paths[i] != NULL)
		{
			ft_get_full_path(paths[i], &full_path, *tokens[0], exec_path);
			if (ft_check_access(exec_path, paths) == 1)
				return (0);
			free(*exec_path);
		i++;
		}
	}
	if (ft_check_script(exec_path, *tokens[0], paths) == 1)
		return (0);
	if (*paths != NULL)
		ft_free_twod_memory(paths);
	if (ft_strchr((const char *)*exec_path, '/') == NULL)
		exit(127);
	exit(126);
}
