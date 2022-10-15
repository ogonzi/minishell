/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:36:03 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/15 17:03:40 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_cmd_line
{
	char				*cmd;
	struct s_token		*word;
	struct s_cmd_line	*next;
}						t_cmd_line;

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

typedef struct s_token
{
	char				*word;
	enum e_type			type;
	struct	s_token		*next;
}						t_token;

/* signals.c */

void	set_sigint_action(void);
void	set_child_sigaction(void);
void	do_sigign(int signum);

/* exec.c */

void	exec(char ***tokens);

/* get_exec_path.c */

int		get_exec_path(char ***tokens, char **exec_path);

#endif
