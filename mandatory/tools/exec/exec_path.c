/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:43:38 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/10 16:17:51 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_exec.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

static t_bool	ft_check_command(char **path_line, char ***paths,
					char *token, char **exec_path);
static t_bool	ft_check_script(char **exec_path, char *first_arg,
					char **paths, t_list **command);

t_bool	get_exec_path(char *token, char **exec_path,
			t_list *command, t_prompt *prompt)
{
	char	**paths;
	char	*path_line;

	path_line = ft_strdup(ft_env_iter(prompt->env, "PATH")->env_data);
	if (ft_check_command(&path_line, &paths, token, exec_path))
		return (FALSE);
	if (ft_check_script(exec_path, token, paths, &command))
	{
		if (path_line)
			ft_delete(path_line);
		return (FALSE);
	}
	if (*paths)
		ft_memfree(paths);
	if (!ft_strchr((const char *)*exec_path, '/'))
	{
		if (path_line)
			ft_delete(path_line);
		((t_cmdline *)command->data)->exit_status = CMD_NOT_FOUND;
		return (TRUE);
	}
	if (path_line)
		ft_delete(path_line);
	((t_cmdline *)command->data)->exit_status = CANNOT_EXEC_CMD;
	return (TRUE);
}

static t_bool	ft_check_command(char **path_line, char ***paths,
				char *token, char **exec_path)
{
	char		*full_path;
	ssize_t		idx;

	if (*path_line)
	{
		*paths = ft_split(*path_line, ':');
		if (*paths == NULL)
			terminate(ERR_MEM, EXIT_FAILURE);
		idx = -1;
		while ((*paths)[++idx])
		{
			ft_get_full_path((*paths)[idx], &full_path, token, exec_path);
			if (ft_check_access(exec_path, *paths))
			{
				ft_delete(*path_line);
				return (TRUE);
			}
			ft_delete(*exec_path);
		}
	}
	return (FALSE);
}

static t_bool	ft_check_script(char **exec_path, char *first_arg,
					char **paths, t_list **command)
{
	*exec_path = ft_strdup(first_arg);
	if (!(*exec_path))
		terminate(ERR_MEM, EXIT_FAILURE);
	if (ft_check_access(exec_path, paths))
	{
		if (!ft_strchr((const char *)*exec_path, '/'))
			((t_cmdline *)(*command)->data)->exit_status = 127;
		return (TRUE);
	}
	return (FALSE);
}

void	ft_get_full_path(char *path, char **full_path, char *user_exec_path,
			char **exec_path)
{
	*full_path = ft_strjoin(path, "/");
	if (!(*full_path))
		terminate(ERR_MEM, EXIT_FAILURE);
	*exec_path = ft_strjoin(*full_path, user_exec_path);
	if (!(*exec_path))
		terminate(ERR_MEM, EXIT_FAILURE);
	ft_delete(*full_path);
}

t_bool	ft_check_access(char **exec_path, char **paths)
{
	if (access(*exec_path, X_OK) == 0)
	{
		if (!(*paths))
			ft_memfree(paths);
		return (TRUE);
	}
	return (FALSE);
}
