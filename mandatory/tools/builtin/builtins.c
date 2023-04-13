/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:56:38 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/13 18:22:43 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_builtins.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

int	check_ft_builtins(t_prompt *prompt, t_pipe pipe_helper,
	int tmp_fd[2], char **av)
{
	char	*builtcmp[7];
	int		idx;

	builtcmp[0] = "pwd";
	builtcmp[1] = "env";
	builtcmp[2] = "exit";
	builtcmp[3] = "echo";
	builtcmp[4] = "export";
	builtcmp[5] = "unset";
	builtcmp[6] = "cd";
	idx = -1;
	while (++idx < 7)
	{
		if (!ft_strncmp(ft_strlowcase(av[0]), builtcmp[idx], ft_strlen(av[0])))
		{
			if (pipe(pipe_helper.fd))
				ft_prompt_clear(prompt, ERR_PIPE, EXIT_FAILURE);
			if (!pipe_helper.is_last)
			{
				if (dup2(pipe_helper.fd[0], tmp_fd[0]) == ERRNUM)
					ft_prompt_clear(prompt, ERR_DUP, EXIT_FAILURE);
				if (close(pipe_helper.fd[0]))
					ft_prompt_clear(prompt, ERR_CLOSE, EXIT_FAILURE);
				if (close(pipe_helper.fd[1]))
					ft_prompt_clear(prompt, ERR_CLOSE, EXIT_FAILURE);
			}
			else
			{
				if (close(pipe_helper.fd[0]))
					terminate(ERR_CLOSE, EXIT_FAILURE);
				if (dup2(pipe_helper.fd[1], tmp_fd[1]) == ERRNUM)
					terminate(ERR_DUP, EXIT_FAILURE);
				if (close(pipe_helper.fd[1]))
					terminate(ERR_CLOSE, EXIT_FAILURE);
			}
			ft_printf_fd(pipe_helper.fd[1], "here should go a builtin\n");
			return (0);
		}
	}
	return (-1);
}

int	ft_builtins(t_prompt *prompt, size_t ac, char **av, char **ev)
{
	if (!ft_strncmp(ft_strlowcase(av[0]), "pwd", ft_strlen(av[0])))
		return (ft_pwd(ac, prompt));
	else if (!ft_strncmp(ft_strlowcase(av[0]), "env", ft_strlen(av[0])))
		return (ft_env(ac, av, ev));
	else if (!ft_strncmp(ft_strlowcase(av[0]), "exit", ft_strlen(av[0])))
		ft_exit(ac, av);
	else if (!ft_strncmp(ft_strlowcase(av[0]), "echo", ft_strlen(av[0])))
		return (ft_echo(ac, av));
	else if (!ft_strncmp(ft_strlowcase(av[0]), "export", ft_strlen(av[0])))
		return (ft_export(ac, av, prompt));
	else if (!ft_strncmp(ft_strlowcase(av[0]), "unset", ft_strlen(av[0])))
		return (ft_unset(ac, av, prompt));
	else if (!ft_strncmp(ft_strlowcase(av[0]), "cd", ft_strlen(av[0])))
		return (ft_cd(ac, av, prompt));
	return (-1);
}
