/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:45:33 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/16 16:26:54 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_error.h"

void	terminate(char *str, int syserr)
{
	ft_printf_fd(STDERR_FILENO, "%s%s", ERR_MSG, str);
	exit(syserr);
}

int	ft_print_error(char *str, int syserr)
{
	ft_printf_fd(STDERR_FILENO, "msh: %s: %s", ERR_MSG, str);
	return (syserr);
}

void	ft_prompt_clear(t_prompt *prompt, char *str, int syserr)
{
	if (prompt->cmdline)
		ft_cmdline_clear(&prompt->cmdline, (void *)ft_delete);
	if (prompt->env)
		ft_env_clear(&prompt->env, (void *)ft_delete);
	if (prompt->export)
		ft_env_clear(&prompt->export, (void *)ft_delete);
	ft_delete(prompt);
	if (str && syserr)
		terminate(str, syserr);
}

void	aux_clean_cmd_env(char ***cmd, char ***env)
{
	ft_memfree((*cmd));
	ft_memfree((*env));
}

void	cmd_not_found(char *cmd)
{
	ft_printf_fd(STDERR_FILENO, "msh: %s: command not found\n",
		cmd);
	exit(CMD_NOT_FOUND);
}
