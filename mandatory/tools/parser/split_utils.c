/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:07:50 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/16 16:52:50 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_parser.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

void	find_closing_quote(char *line, ssize_t *idx, t_bool *f_quote,
	char quote)
{
	*f_quote = TRUE;
	(*idx)++;
	while (line[*idx] && line[*idx] != quote)
		(*idx)++;
	if (line[*idx] == quote)
		*f_quote = FALSE;
}

void	move_to_end_of_quote(char *line, ssize_t *idx)
{
	t_bool	f_quote;

	f_quote = FALSE;
	if (line[*idx] == '\'')
		find_closing_quote(line, idx, &f_quote, '\'');
	if (line[*idx] == '\"')
		find_closing_quote(line, idx, &f_quote, '\"');
}

int	syntax_error(char *word)
{
	ssize_t	idx;

	idx = 0;
	while (word[idx])
	{
		while (ft_strchr("><;#&", word[idx]) == 0 && word[idx])
		{
			move_to_end_of_quote(word, &idx);
			idx++;
		}
		if (word[idx] == '<')
			return (ft_perror_syntax("`<'"));
		if (word[idx] == '>')
			return (ft_perror_syntax("`>'"));
		if (word[idx] == ';')
			return (ft_perror_syntax("`;'"));
		if (word[idx] == '#')
			return (ft_perror_syntax("`newline'"));
		if (word[idx] == '&')
			return (ft_perror_syntax("`&'"));
	}
	return (0);
}

int	ft_perror_syntax(const char *token)
{
	ft_printf_fd(STDERR_FILENO, "msh: %s %s\n", ERR_SYNTAX, token);
	return (258);
}

void	set_opposite_binary(int *value)
{
	if (*value == 1)
		*value = 0;
	else
		*value = 1;
}
