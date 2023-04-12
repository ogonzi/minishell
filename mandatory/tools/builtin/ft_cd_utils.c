/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:32:13 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/12 19:48:09 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_builtins.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

void	get_pwd(char **pwd, t_prompt **prompt)
{
	t_env	*aux;

	aux = ft_env_iter((*prompt)->env, "PWD");
	if (!aux)
		before_export_pwd(prompt);
	*pwd = ft_strdup(aux->env_data);
	if (!(*pwd))
		terminate(ERR_MEM, 1);
	if (ft_env_iter((*prompt)->env, "OLDPWD"))
	{
		ft_swap_content(&ft_env_iter((*prompt)->env, "OLDPWD")->env_data,
			&ft_env_iter((*prompt)->env, "PWD")->env_data);
		ft_swap_content(&ft_env_iter((*prompt)->export, "OLDPWD")->env_data,
			&ft_env_iter((*prompt)->export, "PWD")->env_data);
	}
	else
		before_export_oldpwd(prompt);
}

void	get_homepwd(char **pwd, t_prompt **prompt)
{
	if (!ft_env_iter((*prompt)->env, "PWD"))
		before_export_pwd(prompt);
	if (!ft_env_iter((*prompt)->env, "HOME"))
	{
		*pwd = NULL;
		ft_printf_fd(STDERR_FILENO, "msh: cd: %s", ERR_HOME);
	}
	else
	{
		*pwd = ft_strdup(ft_env_iter((*prompt)->env, "HOME")->env_data);
		if (!(*pwd))
			terminate(ERR_MEM, 1);
		if (ft_env_iter((*prompt)->env, "OLDPWD"))
		{
			ft_swap_content(&ft_env_iter((*prompt)->env, "OLDPWD")->env_data,
				&ft_env_iter((*prompt)->env, "PWD")->env_data);
			ft_swap_content(&ft_env_iter((*prompt)->export, "OLDPWD")->env_data,
				&ft_env_iter((*prompt)->export, "PWD")->env_data);
		}
		else
			before_export_oldpwd(prompt);
	}
}

void	get_oldpwd(char **pwd, t_prompt **prompt)
{
	if (!ft_env_iter((*prompt)->env, "OLDPWD"))
	{
		*pwd = NULL;
		ft_printf_fd(STDERR_FILENO, "msh: cd: %s", ERR_OLDPWD);
	}
	else
	{
		if (!ft_env_iter((*prompt)->env, "PWD"))
			before_export_pwd(prompt);
		*pwd = ft_strdup(ft_env_iter((*prompt)->env, "OLDPWD")->env_data);
		if (!(*pwd))
			terminate(ERR_MEM, 1);
		ft_swap_content(&ft_env_iter((*prompt)->env, "OLDPWD")->env_data,
			&ft_env_iter((*prompt)->env, "PWD")->env_data);
		ft_swap_content(&ft_env_iter((*prompt)->export, "OLDPWD")->env_data,
			&ft_env_iter((*prompt)->export, "PWD")->env_data);
		printf("%s\n", *pwd);
	}
}

int	get_rootpwd(t_prompt **prompt)
{
	char	*pwd;

	if (!ft_env_iter((*prompt)->env, "PWD"))
		before_export_pwd(prompt);
	pwd = ft_strdup("/");
	if (!pwd)
		ft_prompt_clear((*prompt), ERR_MEM, EXIT_FAILURE);
	if (ft_env_iter((*prompt)->env, "OLDPWD"))
	{
		ft_swap_content(&ft_env_iter((*prompt)->env, "OLDPWD")->env_data,
			&ft_env_iter((*prompt)->env, "PWD")->env_data);
		ft_swap_content(&ft_env_iter((*prompt)->export, "OLDPWD")->env_data,
			&ft_env_iter((*prompt)->export, "PWD")->env_data);
	}
	else
		before_export_oldpwd(prompt);
	if (!chdir(pwd))
	{
		ft_env_iter((*prompt)->env, "PWD")->env_data = pwd;
		ft_env_iter((*prompt)->export, "PWD")->env_data = pwd;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void	aux_ft_cd(t_cd_vals *data, t_prompt *prompt)
{
	while (data->dirpwd)
	{
		if (!ft_strncmp(data->segments[data->idx], data->dirpwd->d_name,
				ft_strlen(data->segments[data->idx])))
		{
			data->pwd = ft_strjoin(data->pwd, ft_strjoin(ft_strdup("/"),
						data->segments[data->idx]));
			if (!data->pwd)
				terminate(ERR_MEM, EXIT_FAILURE);
			do_pwd(&prompt, data->pwd);
			break ;
		}
		data->dirpwd = readdir(data->dp);
	}
}
