/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 23:53:49 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/03 15:45:40 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

# include <stddef.h>
# include "libft.h"

typedef struct s_cmd_line_data	t_cmd_line_data;
typedef struct s_prompt			t_prompt;
typedef struct s_environ_data	t_environ_data;
typedef struct s_pipe			t_pipe;
typedef struct s_token_data		t_token_data;
typedef struct s_word			t_word;
typedef struct s_split_data		t_split_data;
typedef struct s_mshenv			t_mshenv;

struct s_cmd_line_data
{
	char	*cmd;
	t_list	*word;
	int		exit_status;
};

struct s_prompt
{
	t_list	*cmd_line;
	t_list	*environ;
	pid_t	pid;
	int		exit_status;
};

struct s_pipe
{
	int	fd[2];
	int	did_out_redirection;
	int	is_last;
};

struct s_environ_data
{
	char	*env_var;
};

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
	EXIT_FILE_APP,
	SYN_ERROR,
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