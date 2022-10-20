/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:02:25 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/20 17:14:54 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <stdio.h>

int	count_num_splits(char *line, char sep)
{
	int	i;
	int	num_splits;
	int	quote_flag;

	quote_flag = 0;
	num_splits = 1;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
			find_closing_quote(line, &i, &quote_flag, '\'');
		if (line[i] == '\"')
			find_closing_quote(line, &i, &quote_flag, '\"');
		if (line[i] == sep)
			num_splits++;
		i++;
	}
	return (num_splits);
}

int	get_splits(char *line, char sep, char ***split_line)
{
	int	start_split;
	int	i;
	int	quote_flag;
	int	split_num;

	i = 0;
	start_split = 0;
	quote_flag = 0;
	split_num = 0;
	while (line[i] != '\0')
	{
		if (i == 0 && line[i] == sep)
			return (1);
		if (line[i] == '\'')
			find_closing_quote(line, &i, &quote_flag, '\'');
		if (line[i] == '\"')
			find_closing_quote(line, &i, &quote_flag, '\"');
		if (line[i] == sep)
		{
			(*split_line)[split_num] = ft_substr(line, start_split, i - start_split);
			if ((*split_line)[split_num] == NULL)
				terminate(ERR_MEM, 1);
			split_num++;
			start_split = i + 1;
		}
		if (line[i + 1] == '\0')
		{
			(*split_line)[split_num] = ft_substr(line, start_split, i + 1 - start_split);
			if ((*split_line)[split_num] == NULL)
				terminate(ERR_MEM, 1);
			split_num++;
		}
		i++;
	}
	(*split_line)[split_num] = NULL;
	return (0);
}

void	ft_split_mod(char ***split_line, char *line, char sep)
{
	int		num_splits;

	num_splits = count_num_splits(line, sep);
	*split_line = malloc(sizeof(char *) * (num_splits + 1));
	if (*split_line == NULL)
		terminate(ERR_MEM, 1);
	if (get_splits(line, sep, split_line) == 1)
		printf("error parsing\n");
}
