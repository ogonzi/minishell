/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mnshll_parser.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:16:29 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/08 18:17:06 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNSHLL_PARSER_H
# define MNSHLL_PARSER_H

# include "libft.h"
# include "ft_printf_fd.h"

# include "mnshll_data.h"

// Parser Functions beelow
//
// Parser Functions (split)
int		split_cmd_line(t_prompt *prompt, char *line);
void	set_node(char **split_line, t_list **cmd_line_node);
int		check_quotes(char *line);

// Parser Util Functions (split utils)
void	find_closing_quote(char *line, ssize_t *i, t_bool *f_quote,	char quote);
void	move_to_end_of_quote(char *line, ssize_t *idx);

// Parser Split
int		ft_split_mod(char ***split_line, char *line, char *sep);
size_t	count_splits(char *line, char *sep);
int		get_splits(char *line, char *sep, char ***split_line);

// Parser Split Utils
int		all_sep(char *line, int idx, char *sep);
void	set_split(char ***split_line, t_split_data *split, char *line, int idx);
int		syntax_error(char *word);
int		ft_perror_syntax(const char *token);
void	set_opposite_binary(int *value);

#endif
