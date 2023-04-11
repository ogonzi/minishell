/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mnshll_data.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:14:06 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/11 16:24:54 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNSHLL_DATA_H
# define MNSHLL_DATA_H

# include <stddef.h>
# include "libft.h"

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
	ERROR,
};

typedef struct s_cmdline		t_cmdline;
typedef struct s_env			t_env;
typedef struct s_prompt			t_prompt;
typedef struct s_pipe			t_pipe;
typedef struct s_word			t_word;
typedef struct s_token			t_token;
typedef struct s_split_data		t_split_data;
typedef struct s_expander_wlen	t_expander_wlen;

struct s_word
{
	char		*str;
	ssize_t		start;
	ssize_t		end;
	enum e_type	*last_type;
};

struct s_cmdline
{
	char				*cmd;
	t_list				*word;
	int					exit_status;
	struct s_cmdline	*next;
};

struct s_env
{
	char			*env_var;
	char			*env_data;
	int				idx;
	struct s_env	*next;
};

struct s_prompt
{
	t_list	*cmdline;
	t_env	*env;
	t_env	*export;
	pid_t	pid;
	int		error_status;
	int		exit_status;
};

struct s_pipe
{
	int	fd[2];
	int	did_out_redirection;
	int	is_last;
};

struct s_token
{
	char				*word;
	enum e_type			type;
	struct s_token		*next;
};

struct s_split_data
{
	int	start;
	int	end;
	int	num;
};

struct s_expander_wlen
{
	ssize_t	idx;
	int		base_length;
	int		added_length;
};

#endif