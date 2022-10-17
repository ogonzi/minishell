/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:36:03 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/17 18:26:50 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"

typedef struct s_cmd_line_content
{
	char	*cmd;
	//t_list	*word;
}			t_cmd_line_content;

enum	e_type
{
	NONE,
	ARG,
	FILE_IN,
	HERE_DOC,
	FILE_OUT,
	FILE_OUT_AC,
	OPEN_FILE,
	LIMITOR,
	EXIT_FILE,
	EXIT_FILE_RET,
};

typedef struct s_token_content
{
	char				*word;
	enum e_type			type;
}						t_token_content;

/* signals.c */

void	set_sigint_action(void);
void	set_child_sigaction(void);
void	do_sigign(int signum);

/* split_cmd_line.c */

void	split_cmd_line(t_list *cmd_line, char *line); 

/* exec.c */

void	exec(char ***tokens);

/* get_exec_path.c */

int		get_exec_path(char ***tokens, char **exec_path);

#endif
