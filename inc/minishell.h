/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:36:03 by ogonzale          #+#    #+#             */
/*   Updated: 2023/01/23 19:01:39 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Our C library and output library
# include "libft.h"
# include "ft_printf.h"
# include "ft_printf_fd.h"

// Other includes
# include "minishell_structs.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

/* signals.c */
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
			enum e_type *last_word_type, t_cmd_line_data *cmd_line);

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

int		redir_pipe(t_list *command_cpy, t_prompt prompt, int tmp_fd[2]);

/* get_exec_path.c */

int		get_exec_path(char *token, char **exec_path,
			t_list *command, t_prompt *prompt);

/* redir_in.c */

int		dup_to_in(int *tmp_fd_in, t_list *command);

/* redir_out.c */

int		dup_to_out(int *tmp_fd_out, t_list *command, int *did_out_redirection);

// Minishell rc file
void	read_banner(void);

#endif
