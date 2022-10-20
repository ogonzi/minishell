/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:07:20 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/20 16:31:55 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

