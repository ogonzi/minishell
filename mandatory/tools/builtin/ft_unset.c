/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:47:08 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/11 19:59:18 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_builtins.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

static int	error_export(char *str);
void		ft_env_delete(t_env **env, char *ref);

int	ft_unset(int ac, char **av, t_prompt *prompt)
{
	ssize_t	cnt;

	if (ac == 1)
		return (0);
	cnt = 0;
	while (av[++cnt])
	{
		if (av[cnt][0] == '=')
			error_export(av[cnt]);
		ft_env_delete(&prompt->env, av[cnt]);
		ft_env_delete(&prompt->export, av[cnt]);
	}
	return (EXIT_SUCCESS);
}

static int	error_export(char *str)
{
	ft_printf_fd(STDERR_FILENO, "mns: unset: \'%s\': %s", str, ERR_EXP);
	return (EXIT_FAILURE);
}

void	ft_env_delete(t_env **env, char *ref)
{
	t_env	*prev;
	t_env	*node;

	if (!env || !*env || !ref)
		return ;
	prev = NULL;
	node = *env;
	while (node)
	{
		if (!ft_strcmp(node->env_var, ref))
		{
			if (prev)
				prev->next = node->next;
			else
				*env = node->next;
			free(node->env_var);
			free(node->env_data);
			free(node);
			break ;
		}
		prev = node;
		node = node->next;
	}
}
