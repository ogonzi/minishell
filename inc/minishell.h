/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:36:03 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/03 18:01:19 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

typedef struct s_cmd_line_content
{
	char	*cmd;
	t_list	*word;
}			t_cmd_line_content;

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

typedef struct s_token_content
{
	char				*word;
	enum e_type			type;
}						t_token_content;

typedef struct s_word
{
	char		*str;
	int			start;
	int			end;
	enum e_type	*last_type;
}				t_word;

/* signals.c */

void	set_sigint_action(void);
void	set_child_sigaction(void);
void	do_sigign(int signum);

/* split_cmd_line.c */

int		split_cmd_line(t_list **cmd_line, char *line);

/* split.c */

int		ft_split_mod(char ***split_line, char *line, char *sep);

/* split_words.c */

int		split_words(t_list **cmd_line);
void	set_token_node(char *word, t_list **token_node,
			enum e_type *last_word_type);

/* split_words_2.c */

int		redirection_conditions(char *split_cmd);
int		check_syntax_error(t_list **cmd_line);

/* split_words_3 */

void	handle_redirection_split(char *split_cmd, t_list **token_node,
			enum e_type *last_word_type, t_cmd_line_content *cmd_line);

/* expand_words.c */

int		expand_words(t_list **cmd_line);

/* expand_words_2.c */

void	expand(char *word, int *remove_char);

/* free.c */

void	free_cmd_line(t_list **cmd_line);

/* exec.c */

void	exec(char ***tokens);

/* get_exec_path.c */

int		get_exec_path(char ***tokens, char **exec_path);

#endif
