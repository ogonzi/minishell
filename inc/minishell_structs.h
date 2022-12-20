/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 23:53:49 by cpeset-c          #+#    #+#             */
/*   Updated: 2022/12/14 23:57:25 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

# include <stddef.h>

typedef struct s_cmd_line_data	t_cmd_line_data;
typedef struct s_token_data		t_token_data;
typedef struct s_word			t_word;
typedef struct s_split_data		t_split_data;

enum	e_type
{
	NONE,
	ARG,
	FILE_IN,
	HERE_DOC,
	FILE_OUT,
	FILE_OUT_APP,
	OPEN_FILE,
	LIMITOR,
	EXIT_FILE,
	EXIT_FILE_RET,
	SYN_ERROR,
};

struct s_cmd_line_data
{
	char	*cmd;
	t_list	*word;
};

struct s_token_data
{
	char				*word;
	enum e_type			type;
};

struct s_word
{
	char		*str;
	int			start;
	int			end;
	enum e_type	*last_type;
};

struct s_split_data
{
	int	start;
	int	end;
	int	num;
};

#endif