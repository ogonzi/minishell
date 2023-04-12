/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:32:13 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/12 12:51:22 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_builtins.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

void	ft_swap_content(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	export_oldpwd(t_prompt **prompt)
{
	char	*pwd;
	char	**args;

	pwd = ft_env_iter((*prompt)->env, "PWD")->env_data;
	args = ft_calloc(sizeof(char *), 4);
	if (!args)
		terminate(ERR_MEM, 1);
	args[0] = ft_strdup("export");
	args[1] = ft_strdup("OLDPWD");
	args[2] = ft_strdup(pwd);
	if (!args[0] || !args[1] || !args[2])
		terminate(ERR_MEM, 1);
	ft_export(3, args, *prompt);
	ft_memfree(args);
}

void	get_pwd(char **pwd, t_prompt **prompt)
{
	t_env	*aux;

	aux = ft_env_iter((*prompt)->env, "PWD");
	if (!aux)
	{
		*pwd = NULL;
		ft_printf_fd(STDERR_FILENO, "msh: cd: %s\n", ERR_CDPWD);
	}
	else
	{
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
			export_oldpwd(prompt);
		ft_env_iter((*prompt)->env, "PWD")->env_data = *pwd;
	}
}

void	get_homepwd(char **pwd, t_prompt **prompt)
{
	t_env	*cpy;
	t_env	*aux;

	cpy = ft_env_iter((*prompt)->env, "HOME");
	aux = ft_env_iter((*prompt)->env, "PWD");
	if (!cpy || !aux)
		*pwd = NULL;
	else
	{
		*pwd = ft_strdup(cpy->env_data);
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
			export_oldpwd(prompt);
		ft_env_iter((*prompt)->env, "PWD")->env_data = *pwd;
		ft_env_iter((*prompt)->export, "PWD")->env_data = *pwd;
	}
}

void	get_oldpwd(char **pwd, t_prompt **prompt)
{
	t_env	*cpy;
	t_env	*aux;

	cpy = ft_env_iter((*prompt)->env, "OLDPWD");
	aux = ft_env_iter((*prompt)->env, "PWD");
	if (!cpy || !aux)
	{
		*pwd = NULL;
		ft_printf_fd(STDERR_FILENO, "msh: cd: %s\n", ERR_OLDPWD);
	}
	else
	{
		*pwd = ft_strdup(cpy->env_data);
		if (!(*pwd))
			terminate(ERR_MEM, 1);
		ft_env_iter((*prompt)->env, "PWD")->env_data = *pwd;
		ft_swap_content(&cpy->env_data, &aux->env_data);
		ft_swap_content(&ft_env_iter((*prompt)->export, "OLDPWD")->env_data,
			&ft_env_iter((*prompt)->export, "PWD")->env_data);
		printf("%s\n", *pwd);
	}
}
