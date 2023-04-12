/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:10:30 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/12 12:53:03 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_builtins.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

static int	do_homepwd(t_prompt **prompt);
static int	do_rootpwd(void);
static int	do_oldpwd(t_prompt **prompt);
static int	aux_ft_cd(t_prompt *prompt, char **av, DIR *dp,
				struct dirent *dirpwd);

int	ft_cd(int ac, char **av, t_prompt *prompt)
{
	DIR				*dp;
	struct dirent	*dirpwd;

	dp = NULL;
	dirpwd = NULL;
	if (ac == 1)
		return (do_homepwd(&prompt));
	else if ((av[1][0] == '~' && !av[1][1]) ||
			(av[1][0] == '~' && av[1][1] == '/' && !av[1][2]))
		return (do_homepwd(&prompt));
	else if (av[1][0] == '/' && !av[1][1])
		return (do_rootpwd());
	else if (av[1][0] == '-' && !av[1][1])
		return (do_oldpwd(&prompt));
	else
		return (aux_ft_cd(prompt, av, dp, dirpwd));
	return (EXIT_SUCCESS);
}

static int	aux_ft_cd(t_prompt *prompt, char **av, DIR *dp,
	struct dirent *dirpwd)
{
	char	*pwd;

	get_pwd(&pwd, &prompt);
	dp = opendir(pwd);
	if (!dp)
		return (EXIT_FAILURE);
	dirpwd = readdir(dp);
	while (dirpwd)
	{
		if (!ft_strncmp(av[1], dirpwd->d_name, ft_strlen(av[1])))
		{
			pwd = ft_strjoin(pwd, ft_strjoin(ft_strdup("/"), dirpwd->d_name));
			if (!pwd)
				terminate(ERR_MEM, 1);
			ft_env_iter((prompt)->env, "PWD")->env_data = pwd;
			ft_env_iter((prompt)->export, "PWD")->env_data = pwd;
			if (chdir(pwd))
				return (EXIT_FAILURE);
			break ;
		}
		dirpwd = readdir(dp);
	}
	if (closedir(dp) == ERRNUM)
		ft_printf_fd(STDERR_FILENO, "Failed to close dir.\n");
	return (EXIT_SUCCESS);
}

static int	do_homepwd(t_prompt **prompt)
{
	char	*pwd;

	get_homepwd(&pwd, prompt);
	if (!chdir(pwd))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static int	do_rootpwd(void)
{
	if (!chdir("/"))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static int	do_oldpwd(t_prompt **prompt)
{
	char	*pwd;

	get_oldpwd(&pwd, prompt);
	if (!chdir(pwd))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
