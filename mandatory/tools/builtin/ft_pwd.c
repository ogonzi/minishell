/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:38:27 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/13 18:19:27 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_builtins.h"
#include "mnshll_error.h"

int	ft_pwd(size_t ac, t_prompt *prompt)
{
	char	*str;

	if (ac > 1)
		terminate(ERR_PWD, EXIT_FAILURE);
	str = ft_strdup(ft_env_iter(prompt->env, "PWD")->env_data);
	if (!str)
		ft_prompt_clear(prompt, ERR_MEM, EXIT_FAILURE);
	ft_printf_fd(STDIN_FILENO, "%s\n", str);
	ft_delete(str);
	return (EXIT_SUCCESS);
}
