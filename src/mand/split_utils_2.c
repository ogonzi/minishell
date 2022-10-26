/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:04:01 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/26 19:09:21 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <stdio.h>

int	print_error_syntax(const char *token)
{
	printf("%s %s\n", ERR_SYNTAX, token);
	return (1);
}

int	syntax_error(char *word, int word_len)
{
	if (word_len == 1)
	{
		if (ft_is_in_set('<', word) == 1)
			return (print_error_syntax("`<'"));
		else if (ft_is_in_set('>', word) == 1)
			return (print_error_syntax("`>'"));
	}
	else
	{
		if (ft_is_in_set('<', word) == 1)
			return (print_error_syntax("`<<'"));
		else if (ft_is_in_set('>', word) == 1)
			return (print_error_syntax("`>>'"));
	}
	return (0);
}
