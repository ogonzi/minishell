/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:56:38 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/10 17:51:45 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_builtins.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

void	check_ft_builtins(t_prompt *prompt, size_t	ac, char **av, char **ev)
{
	UNUSED(ev);
	UNUSED(prompt);
	if (ac < 0)
		terminate(ERR_ARGS, 1);
	if (!ft_strncmp(ft_strlowcase(av[0]), "pwd", ft_strlen(av[0])))
		ft_pwd(ac, ev);
	else if (!ft_strncmp(ft_strlowcase(av[0]), "env", ft_strlen(av[0])))
		printf("here shoud be env\n");
	else if (!ft_strncmp(ft_strlowcase(av[0]), "exit", ft_strlen(av[0])))
		printf("here shoud be exit\n");
	else if (!ft_strncmp(ft_strlowcase(av[0]), "echo", ft_strlen(av[0])))
		printf("here shoud be echo\n");
	else if (!ft_strncmp(ft_strlowcase(av[0]), "export", ft_strlen(av[0])))
		printf("here shoud be export\n");
	else if (!ft_strncmp(ft_strlowcase(av[0]), "unset", ft_strlen(av[0])))
		printf("here shoud be unset\n");
	else if (!ft_strncmp(ft_strlowcase(av[0]), "cd", ft_strlen(av[0])))
		printf("here shoud be cd\n");
	else
		return ;
	exit(0);
}
