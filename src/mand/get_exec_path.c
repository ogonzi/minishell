/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:39:10 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/16 17:12:44 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "minishell.h"
#include <stdio.h>

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

int	ft_check_script(char **exec_path, char *first_arg,
					char **paths, t_list **command)
{
	*exec_path = ft_strdup(first_arg);
	if (!(*exec_path))
		terminate(ERR_MEM, 1);
	if (ft_check_access(exec_path, paths) == 1)
	{
		if (ft_strchr((const char *)*exec_path, '/') == NULL)
			((t_cmd_line_content *)(*command)->content)->exit_status = 127;
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

int	get_exec_path(char *token, char **exec_path,
					t_list *command, t_prompt *prompt)
{
	char	**paths;
	char	*path_line;
	char	*full_path;
	int		i;

	path_line = custom_getenv("PATH", prompt);
	paths = NULL;
	if (path_line != NULL)
	{
		paths = ft_split(path_line, ':');
		if (paths == NULL)
			terminate(ERR_MEM, 1);
		i = 0;
		while (paths[i] != NULL)
		{
			ft_get_full_path(paths[i], &full_path, token, exec_path);
			if (ft_check_access(exec_path, paths) == 1)
			{
				free(path_line);
				return (0);
			}
			free(*exec_path);
		i++;
		}
	}
	if (ft_check_script(exec_path, token, paths, &command) == 1)
	{
		free(path_line);
		return (0);
	}
	if (*paths != NULL)
		ft_free_twod_memory(paths);
	if (ft_strchr((const char *)*exec_path, '/') == NULL)
	{
		free(path_line);
		((t_cmd_line_content *)command->content)->exit_status = 127;
		return (1);
	}
	free(path_line);
	((t_cmd_line_content *)command->content)->exit_status = 126;
	return (1);
}
