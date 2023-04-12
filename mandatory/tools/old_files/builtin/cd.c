/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:39:00 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/12 11:15:17 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	main(int ac, char **av, char **ev)
{
	DIR				*dp;
	struct dirent	*dirpwd;
	char			*pwd;

	if (ac == 1)
	{
		get_homepwd(&pwd, ev);
		if (!chdir(pwd))
			return (0);
		return (1);
	}
	else if ((av[1][0] == '~' && !av[1][1]) ||
		(av[1][0] == '~' && av[1][1] == '/' && !av[1][2]))
	{
		get_homepwd(&pwd, ev);
		if (!chdir(pwd))
			return (0);
		return (1);
	}
	else if (av[1][0] == '/' && !av[1][1])
	{
		if (!chdir(pwd))
			return (0);
	}
	else if (av[1][0] == '-' && !av[1][1])
	{
		get_oldpwd(&pwd, ev);
		if (!chdir(pwd))
			return (0);
		return (1);
	}
	else
	{
		get_pwd(&pwd, ev);
		dp = opendir(pwd);
		if (!dp)
			return (1);
		dirpwd = readdir(dp);
		while (dirpwd)
		{
			if (!ft_strncmp(av[1], dirpwd->d_name, ft_strlen(av[1])))
			{
				pwd = ft_strjoin(pwd, ft_strdup("/"));
				if (!pwd)
					return (1);
				pwd = ft_strjoin(pwd, dirpwd->d_name);
				if (!pwd)
					return (1);
				if (chdir(pwd))
					return (1);
				break ;
			}
			dirpwd = readdir(dp);
		}
		if (closedir(dp) == -1)
			ft_printf_fd(STDERR_FILENO, "Failed to close dir.\n");
	}
	return (0);
}

void	get_pwd(char **pwd, char **ev)
{
	ssize_t	idx;
	ssize_t	count;

	idx = -1;
	count = ft_strlen(PWDCMP);
	while (ev[++idx])
	{
		if (!ft_strncmp(ev[idx], PWDCMP, count))
		{
			while (count--)
				ev[idx]++;
			*pwd = ev[idx];
			return ;
		}
	}
}

void	get_oldpwd(char **pwd, char **ev)
{
	ssize_t	idx;
	ssize_t	count;

	idx = -1;
	count = ft_strlen(OLDPWDCMP);
	while (ev[++idx])
	{
		if (!ft_strncmp(ev[idx], OLDPWDCMP, count))
		{
			while (count--)
				ev[idx]++;
			*pwd = ev[idx];
			printf("%s\n", *pwd);
			return ;
		}
	}
}

void	get_homepwd(char **pwd, char **ev)
{
	ssize_t	idx;
	ssize_t	count;

	idx = -1;
	count = ft_strlen(HOMEPWDCMP);
	while (ev[++idx])
	{
		if (!ft_strncmp(ev[idx], HOMEPWDCMP, count))
		{
			while (count--)
				ev[idx]++;
			*pwd = ev[idx];
			return ;
		}
	}
}
