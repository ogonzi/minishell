/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:36:03 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/17 20:04:11 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>

typedef struct s_cmd_line_content
{
	char	*cmd;
	t_list	*word;
	int		exit_status;
}			t_cmd_line_content;

typedef struct s_prompt
{
	t_list	*cmd_line;
	t_list	*environ;
	pid_t	pid;
	int		exit_status;
}			t_prompt;

typedef struct s_environ_content
{
	char	*env_var;
}			t_environ_content;

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

/* env.c */

void	custom_setenv(char *name, char *value, t_prompt *prompt);
char	*custom_getenv(char *name, t_prompt *prompt);
void	init_env_vars(t_prompt *prompt, char *argv[]);
void	set_environ(t_prompt *prompt, char *envp[]);

/* split_cmd_line.c */

int		split_cmd_line(t_prompt *prompt, char *line);

/* split.c */

int		ft_split_mod(char ***split_line, char *line, char *sep);

/* split_words.c */

int		split_words(t_prompt *prompt);
void	set_token_node(char *word, t_list **token_node,
			enum e_type *last_word_type);

/* split_words_2.c */

int		redirection_conditions(char *split_cmd);
int		check_syntax_error(t_list **cmd_line);

/* split_words_3 */

void	handle_redirection_split(char *split_cmd, t_list **token_node,
			enum e_type *last_word_type, t_cmd_line_content *cmd_line);

/* expand_words.c */

int		expand_words(t_prompt *prompt);

/* expand_words_2.c */

void	expand(char *word, int *remove_char);

/* expand_words_3.c */

char	*expand_env(char *word, int exit_status);

/* free.c */

void	free_cmd_line(t_list **cmd_line);
void	free_environ(t_list **environ);

/* exec.c */

int		redir_pipe(t_list *command_cpy, t_prompt prompt, int *tmp_fd);

/* get_exec_path.c */

int		get_exec_path(char *token, char **exec_path,
			t_list *command, t_prompt *prompt);

#endif
