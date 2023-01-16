/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:02:25 by ogonzale          #+#    #+#             */
/*   Updated: 2023/01/11 13:29:11 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_utils.h"
#include <stdio.h>

int	all_sep(char *line, int i, char *sep)
{
	while (line[i] != '\0')
	{
		if (ft_strchr(sep, line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	count_num_splits(char *line, char *sep)
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
		if (ft_strchr(sep, line[i]) && all_sep(line, i, sep) != 1)
			num_splits++;
		i++;
	}
	return (num_splits);
}

int	no_command_between_pipes(char *str, t_split_data split, char ***split_line)
{
	int	i;

	i = 1;
	while (ft_isspace(str[i]) && str[i] != '\0')
		i++;
	if (str[i] == '\0' || str[i] == '|')
	{
		while (--split.num >= 0)
			free((*split_line)[split.num]);
		return (1);
	}
	return (0);
}

int	get_splits(char *line, char *sep, char ***split_line)
{
	t_split_data	split;
	int				i;

	split.start = 0;
	split.num = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (i == 0 && ft_strchr(sep, line[i]) && sep[0] == '|')
			return (print_error_syntax("`|'"));
		move_to_end_of_quote(line, &i);
		if (ft_strchr(sep, line[i]))
		{
			if (sep[0] == '|')
				if (no_command_between_pipes(&line[i], split, split_line) == 1)
					return (print_error_syntax("`|'"));
			set_split(split_line, &split, line, i);
		}
		if (line[i + 1] == '\0' && split.start != i + 1)
			set_split(split_line, &split, line, i + 1);
		i++;
	}
	(*split_line)[split.num] = NULL;
	return (0);
}

int	ft_split_mod(char ***split_line, char *line, char *sep)
{
	int		num_splits;

	num_splits = count_num_splits(line, sep);
	*split_line = malloc(sizeof(char *) * (num_splits + 1));
	if (*split_line == NULL)
		terminate(ERR_MEM, 1);
	if (get_splits(line, sep, split_line) == 1)
	{
		free(*split_line);
		*split_line = NULL;
		return (1);
	}
	return (0);
}
