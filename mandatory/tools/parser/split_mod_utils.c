/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mod_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:29:06 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/08 12:40:30 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

int	all_sep(char *line, int idx, char *sep)
{
	while (line[idx])
	{
		if (!ft_strchr(sep, line[idx]))
			return (FALSE);
		idx++;
	}
	return (TRUE);
}

void	set_split(char ***split_line, t_split_data *split, char *line, int idx)
{
	if (split->start != idx)
	{
		(*split_line)[split->num] = ft_substr(line, split->start,
				idx - split->start);
		if (!(*split_line)[split->num])
			exit(1);
			// terminate(ERR_MEM, 1);
		split->num++;
		split->start = idx + 1;
	}
	else
		split->start++;
}
