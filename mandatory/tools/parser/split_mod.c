/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:03:53 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/08 12:47:03 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

static int	no_command_between_pipes(char *str, t_split_data split,
				char ***split_line);

int	ft_split_mod(char ***split_line, char *line, char *sep)
{
	size_t	nsplits;

	nsplits = count_splits(line, sep);
	*split_line = malloc(sizeof(char *) * (nsplits + 1));
	if (!split_line)
		return (FALSE);
		//terminate()
	if (get_splits(line, sep, split_line) == TRUE)
	{
		ft_delete(*split_line);
		return (TRUE);
	}
	return (FALSE);
}

size_t	count_splits(char *line, char *sep)
{
	ssize_t	idx;
	size_t	nsplits;
	t_bool	f_quote;

	idx = -1;
	nsplits = 1;
	f_quote = FALSE;
	while (line[++idx])
	{
		if (line[idx] == '\'')
			find_closing_quote(line, &idx, &f_quote, '\'');
		if (line[idx] == '\"')
			find_closing_quote(line, &idx, &f_quote, '\"');
		if (ft_strchr(sep, line[idx]) && all_sep(line, idx, sep) != 1)
			nsplits++;
	}
	return (nsplits);
}

int	get_splits(char *line, char *sep, char ***split_line)
/*
		The get_splits function takes a string line, a separator string sep,
	and a pointer to an array of strings split_line. It splits the line at the
	occurrence of sep and stores the resulting substrings in split_line.
	The function returns TRUE if an error occurs during the splitting process
	and FALSE otherwise.

		The function uses a t_split_data struct to keep track of the start
	index and the number of substrings found so far. It initializes the start
	index to 0 and the number of substrings to 0. It then loops through each
	character in line and checks if it is a separator character. If it is, the
	function calls the set_split function to store the substring between the
	current start index and the separator index in split_line.

		If sep is the pipe character |, the function also checks if there is a
	valid command between the current separator and the next one. This check is
	performed by calling the no_command_between_pipes function, which returns
	TRUE if there is no command between the pipes and FALSE otherwise.

	Finally, the function sets the last element of split_line to NULL and
	returns FALSE if no errors occurred during the splitting process.
*/
{
	ssize_t			idx;
	t_split_data	sdata;

	idx = 0;
	sdata.start = 0;
	sdata.num = 0;
	while (line[idx] != 0)
	{
		if (idx == 0 && ft_strchr(sep, line[idx]) && sep[0] == '|')
			return (ft_perror_syntax("`|`"));
		move_to_end_of_quote(line, &idx);
		if (ft_strchr(sep, line[idx]))
		{
			if (sep[0] == '|')
				if (no_command_between_pipes(&line[idx], sdata, split_line))
					return (ft_perror_syntax("`|`"));
			set_split(split_line, &sdata, line, idx);
		}
		if (line[idx + 1] == '\0' && sdata.start != idx + 1)
			set_split(split_line, &sdata, line, idx + 1);
		idx++;
	}
	(*split_line)[sdata.num] = NULL;
	return (FALSE);
}

static int	no_command_between_pipes(char *str, t_split_data sdata,
		char ***split_line)
{
	size_t	idx;

	idx = 1;
	while (str[idx] && ft_isspace(str[idx]))
		idx++;
	if (str[idx] == '\0' || str[idx] == '|')
	{
		while (--sdata.num >= 0)
			ft_delete(*split_line[sdata.num]);
		return (TRUE);
	}
	return (FALSE);
}
