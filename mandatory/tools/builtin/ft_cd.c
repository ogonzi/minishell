/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:10:30 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/21 18:00:16 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_builtins.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

static int	before_ft_cd(t_prompt *prompt, char **av);
static int	do_homepwd(t_prompt **prompt);
static int	do_oldpwd(t_prompt **prompt);

int	ft_cd(int ac, char **av, t_prompt *prompt)
{
	if (ac == 1)
		return (do_homepwd(&prompt));
	else
	{
		if ((av[1][0] == '~' && !av[1][1]) ||
				(av[1][0] == '~' && av[1][1] == '/' && !av[1][2]))
			return (do_homepwd(&prompt));
		else if (av[1][0] == '/' && !av[1][1])
			return (get_rootpwd(&prompt));
		else if (av[1][0] == '-' && !av[1][1])
			return (do_oldpwd(&prompt));
		else
			return (before_ft_cd(prompt, av));
	}
	return (EXIT_SUCCESS);
}

static int	before_ft_cd(t_prompt *prompt, char **av)
{
	t_cd_vals	data;

	get_pwd(&data.pwd, &prompt);
	check_valid_path(data.pwd, av[1]);
	data.segments = ft_split(av[1], '/');
	if (!data.segments)
		terminate(ERR_MEM, EXIT_FAILURE);
	data.idx = -1;
	while (data.segments[++data.idx])
	{
		data.dp = opendir(data.pwd);
		if (!data.dp)
			return (EXIT_FAILURE);
		data.dirpwd = readdir(data.dp);
		aux_ft_cd(&data, prompt);
		closedir(data.dp);
	}
	ft_delete(data.pwd);
	ft_memfree(data.segments);
	return (EXIT_SUCCESS);
}

static int	do_homepwd(t_prompt **prompt)
{
	char	*pwd;

	get_homepwd(&pwd, prompt);
	if (!chdir(pwd))
	{
		ft_env_iter((*prompt)->env, "PWD")->env_data = ft_strdup(pwd);
		ft_env_iter((*prompt)->export, "PWD")->env_data = ft_strdup(pwd);
		ft_delete(pwd);
		return (EXIT_SUCCESS);
	}
	ft_delete(pwd);
	return (EXIT_FAILURE);
}

static int	do_oldpwd(t_prompt **prompt)
{
	char	*pwd;

	get_oldpwd(&pwd, prompt);
	if (!chdir(pwd))
	{
		ft_env_iter((*prompt)->env, "PWD")->env_data = ft_strdup(pwd);
		ft_env_iter((*prompt)->export, "PWD")->env_data = ft_strdup(pwd);
		ft_delete(pwd);
		return (EXIT_SUCCESS);
	}
	ft_delete(pwd);
	return (EXIT_FAILURE);
}

int	do_pwd(t_prompt **prompt, char *pwd)
{
	char	*aux;

	aux = NULL;
	if (!chdir(pwd))
	{
		aux = get_custom_pwd();
		if (!aux)
			terminate(ERR_MEM, EXIT_FAILURE);
		ft_env_iter((*prompt)->env, "PWD")->env_data = ft_strdup(aux);
		if (!ft_env_iter((*prompt)->env, "PWD")->env_data)
			terminate(ERR_MEM, EXIT_FAILURE);
		ft_env_iter((*prompt)->export, "PWD")->env_data = ft_strdup(aux);
		if (!ft_env_iter((*prompt)->export, "PWD")->env_data)
			terminate(ERR_MEM, EXIT_FAILURE);
		ft_delete(aux);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
