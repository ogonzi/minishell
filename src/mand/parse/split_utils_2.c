/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:04:01 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/07 11:10:58 by ogonzale         ###   ########.fr       */
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

int	syntax_error(char *word)
{
	int	i;

	i = 0;
	while (word[i] != '\0')
	{
		while (word[i] != '<' && word[i] != '>' && word[i] != '\0')
		{
			move_to_end_of_quote(word, &i);
			i++;
		}
		if (word[i] == '<')
			return (print_error_syntax("`<'"));
		if (word[i] == '>')
			return (print_error_syntax("`>'"));
	}
	return (0);
}

void	set_opposite_binary(int *value)
{
	if (*value == 1)
		*value = 0;
	else
		*value = 1;
}

void	copy_char_to_word(char *word, char *cpy_word,
		int *from_index, int *to_index)
{
	word[*to_index] = cpy_word[*from_index];
	(*from_index)++;
	(*to_index)++;
}
