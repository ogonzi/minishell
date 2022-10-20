/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:07:20 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/20 19:10:45 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
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

int	print_error_syntax(void)
{
	printf("%s %s\n", ERR_SYNTAX, "`|'");
	return (1);
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
	(*split_line)[split->num] = ft_substr(line, split->start, i - split->start);
	if ((*split_line)[split->num] == NULL)
		terminate(ERR_MEM, 1);
	(split->num)++;
	split->start = i + 1;
}
