/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:06:40 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/12 16:12:57 by cpeset-c         ###   ########.fr       */
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

void	export_pwd(t_prompt **prompt)
{
	char	**args;

	args = ft_calloc(sizeof(char *), 4);
	if (!args)
		terminate(ERR_MEM, 1);
	args[0] = ft_strdup("export");
	args[1] = ft_strdup("PWD");
	args[2] = ft_strdup(get_custom_pwd());
	if (!args[0] || !args[1] || !args[2])
		terminate(ERR_MEM, 1);
	ft_export(3, args, *prompt);
	ft_memfree(args);
}
