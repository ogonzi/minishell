/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_auxiliar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:58:46 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/05/01 17:47:30 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_builtins.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

extern int	g_exit_status;

int	check_valid_path(char *path, char *str)
{
	char	*aux;
	char	*tmp;

	aux = ft_strjoin("/", str);
	if (!aux)
		terminate(ERR_MEM, EXIT_FAILURE);
	tmp = ft_strjoin(path, aux);
	if (!tmp)
		terminate(ERR_MEM, EXIT_FAILURE);
	if (!is_valid_path(tmp))
	{
		ft_delete(aux);
		ft_delete(tmp);
		g_exit_status = 1;
		return (EXIT_FAILURE);
	}
	ft_delete(aux);
	ft_delete(tmp);
	return (EXIT_SUCCESS);
}

int	is_valid_path(char *path)
{
	if (access(path, F_OK) != 0)
	{
		ft_printf_fd(STDERR_FILENO, "cd: no such file or directory: %s\n", path);
		return (FALSE);
	}
	if (access(path, X_OK) != 0)
	{
		ft_printf_fd(STDERR_FILENO, "cd: permission denied: %s\n", path);
		return (FALSE);
	}
	return (TRUE);
}

void	aux_ft_cd(t_cd_vals *data, t_prompt *prompt)
{
	char	*aux;

	while (data->dirpwd)
	{
		if (!ft_strncmp(data->segments[data->idx], data->dirpwd->d_name,
				ft_strlen(data->segments[data->idx])))
		{
			aux = ft_strjoin("/", data->segments[data->idx]);
			if (!aux)
				terminate(ERR_MEM, EXIT_FAILURE);
			data->pwd = ft_strjoin(data->pwd, aux);
			if (!data->pwd)
				terminate(ERR_MEM, EXIT_FAILURE);
			ft_delete(aux);
			do_pwd(&prompt, data->pwd);
			break ;
		}
		data->dirpwd = readdir(data->dp);
	}
}

void	before_export_pwd(t_prompt **prompt)
{
	export_pwd(ft_env_last(&(*prompt)->env));
	export_pwd(ft_env_last(&(*prompt)->export));
}

void	before_export_oldpwd(t_prompt **prompt)
{
	export_oldpwd(ft_env_last(&(*prompt)->env));
	export_oldpwd(ft_env_last(&(*prompt)->export));
}
