/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:07:20 by ogonzale          #+#    #+#             */
/*   Updated: 2023/01/11 13:29:11 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void	find_closing_quote(char *line, int *i, int *quote_flag, char quote)
{
	*quote_flag = 1;
	(*i)++;
	while (line[*i] != quote && line[*i] != '\0')
		(*i)++;
	if (line[*i] == quote)
		*quote_flag = 0;
}

int	count_splits(char **split_line)
{
	int	i;

	i = 0;
	while (split_line[i] != NULL)
		i++;
	return (i);
}

void	move_to_end_of_quote(char *line, int *i)
{
	int	quote_flag;

	quote_flag = 0;
	if (line[*i] == '\'')
		find_closing_quote(line, i, &quote_flag, '\'');
	if (line[*i] == '\"')
		find_closing_quote(line, i, &quote_flag, '\"');
}

void	set_split(char ***split_line, t_split_data *split, char *line, int i)
{
	if (split->start != i)
	{
		(*split_line)[split->num]
			= ft_substr(line, split->start, i - split->start);
		if ((*split_line)[split->num] == NULL)
			terminate(ERR_MEM, 1);
		(split->num)++;
		split->start = i + 1;
	}
	else
		split->start++;
}
