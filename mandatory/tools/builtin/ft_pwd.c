/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:38:27 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/19 14:42:02 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_builtins.h"
#include "mnshll_error.h"

int	ft_pwd(size_t ac)
{
	char	*str;

	if (ac > 1)
		terminate(ERR_PWD, EXIT_FAILURE);
	str = get_custom_pwd();
	printf("%s\n", str);
	ft_delete(str);
	return (EXIT_SUCCESS);
}
