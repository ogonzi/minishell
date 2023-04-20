/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:25:43 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/20 14:32:13 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_exec.h"
#include "mnshll_builtins.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

static void	aux_check_execve_valid(char **command_array,
				size_t *idx, char **exec_path);

void	check_execve_valid(char **command_array, char **exec_path,
	t_list *command, t_prompt *prompt)
{
	size_t	idx;

	idx = 0;
	if (command_array[0][0] == '.' && !ft_env_iter(prompt->env, "PATH"))
		cmd_not_found(command_array[0]);
	else if (command_array[0][0] == '/' || command_array[0][0] == '.')
		aux_check_execve_valid(command_array, &idx, exec_path);
	else if (!ft_env_iter(prompt->env, "PATH")
		&& !access(command_array[0], X_OK))
		*exec_path = command_array[0];
	else if (!ft_env_iter(prompt->env, "PATH"))
		cmd_not_found(command_array[0]);
	else if (get_exec_path(command_array[0], exec_path, command, prompt)
		&& access(command_array[0], X_OK))
	{
		cmd_not_found(command_array[0]);
		exit(((t_cmdline *)command->data)->exit_status);
	}
}

static void	aux_check_execve_valid(char **command_array,
	size_t *idx, char **exec_path)
{
	if (!ft_isalnum(command_array[0][ft_strlen(command_array[0]) - 1]))
		cmd_not_found(command_array[0]);
	else if (access(command_array[0], X_OK))
	{
		while (command_array[0][*idx] == '/' || command_array[0][*idx] == '.')
		{
			if (!command_array[0][*idx + 1]
				|| (command_array[0][*idx + 1] != '/'
					|| command_array[0][*idx] != '.'))
				cmd_not_found(command_array[0]);
			(*idx)++;
		}
	}
	else
		*exec_path = command_array[0];
}
