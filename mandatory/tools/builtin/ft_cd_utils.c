/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:32:13 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/05/01 17:47:03 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_builtins.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

void	get_pwd(char **pwd, t_prompt **prompt, t_bool flag)
{
	if (!ft_env_iter((*prompt)->env, "PWD"))
		before_export_pwd(prompt);
	if (flag == TRUE)
		*pwd = ft_strdup("/");
	else if (flag == FALSE)
		*pwd = get_custom_pwd();
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
		ft_env_iter((*prompt)->env, "PWD")->env_data = ft_strdup(pwd);
		ft_env_iter((*prompt)->export, "PWD")->env_data = ft_strdup(pwd);
		ft_delete(pwd);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
