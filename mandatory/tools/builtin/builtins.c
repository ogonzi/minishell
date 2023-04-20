/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:56:38 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/20 19:42:41 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_builtins.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

int	check_ft_builtins1(t_prompt *prompt, char **av, char **ev)
{
	char	*builtcmp1[3];
	char	*builtcmp2[5];
	int		idx;

	builtcmp1[0] = "pwd";
	builtcmp1[1] = "echo";
	builtcmp1[2] = "env";
	builtcmp2[0] = "exit";
	builtcmp2[1] = "export";
	builtcmp2[2] = "unset";
	builtcmp2[3] = "cd";
	idx = -1;
	while (++idx < 3)
	{
		if (!ft_strncmp(av[0], builtcmp1[idx], ft_strlen(av[0])))
			return (ft_builtins(prompt, ft_strcount(av), av, ev));
	}
	idx = -1;
	while (++idx < 5)
	{
		if (!ft_strncmp(av[0], builtcmp2[idx], ft_strlen(av[0])))
			return (-2);
	}
	return (-1);
}

int	check_ft_builtins2(t_prompt *prompt, t_pipe pipe_helper,
	char **av, char **ev)
{
	char	*builtcmp[4];
	int		idx;

	builtcmp[0] = "exit";
	builtcmp[1] = "export";
	builtcmp[2] = "unset";
	builtcmp[3] = "cd";
	idx = -1;
	while ((++idx < 4) && av[0])
	{
		if (!ft_strncmp(av[0], builtcmp[idx], ft_strlen(av[0]))
			&& pipe_helper.is_first == TRUE)
			return (ft_builtins(prompt, ft_strcount(av), av, ev));
	}
	return (-1);
}

int	ft_builtins(t_prompt *prompt, size_t ac, char **av, char **ev)
{
	if (!ft_strncmp(ft_strlowcase(av[0]), "pwd", ft_strlen("pwd")))
		return (ft_pwd(ac));
	else if (!ft_strncmp(ft_strlowcase(av[0]), "env", ft_strlen("env")))
		return (ft_env(ac, av, ev));
	else if (!ft_strncmp(ft_strlowcase(av[0]), "echo", ft_strlen("echo")))
		return (ft_echo(ac, av));
	else if (!ft_strncmp(av[0], "exit", ft_strlen("exit")))
		ft_exit(ac, av);
	else if (!ft_strncmp(av[0], "export", ft_strlen("export")))
		return (ft_export(ac, av, prompt));
	else if (!ft_strncmp(av[0], "unset", ft_strlen("unset")))
		return (ft_unset(ac, av, prompt));
	else if (!ft_strncmp(av[0], "cd", ft_strlen("cd")))
		return (ft_cd(ac, av, prompt));
	return (-1);
}
