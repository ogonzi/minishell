/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:58:30 by ogonzale          #+#    #+#             */
/*   Updated: 2023/01/23 18:52:15 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

# include "minishell_structs.h"

/* Error messages & warnings*/

# define ERR_ARGS			"Incorrect number of arguments, expected 0"
# define ERR_QUOTES			"Opening quotes aren't properly closed"
# define ERR_SYNTAX			"-msh: Syntax error near unexpected token"
# define ERR_GETPWD			"Function error -> getpwd"
# define ERR_MEM			"Function error -> malloc"
# define ERR_SIG			"Function error -> sigaction"
# define ERR_TC_GET_ATTR	"Function error -> tcgetattr"
# define ERR_SIGADDSET		"Function error -> sigaddset"
# define ERR_DUP			"Function error -> dup"
# define ERR_PIPE			"Function error -> pipe"
# define ERR_FORK			"Function error -> fork"
# define ERR_WAIT			"Function error -> wait"
# define ERR_EXECVE			"Function error -> execve"
# define ERR_OPEN			"Function error -> open"
# define ERR_CLOSE			"Function error -> close"
# define ERR_UNLINK			"Function error -> unlink"
# define ERR_CHLD			"Core dump in child"
# define TMP_FILE_HEREDOC	"/tmp/heredoc"
# define ERR_MRC			(char *)"There was an error while reading.\n"
/* Error codes */

# define CATCH_ALL			1
# define SHELL_MISUSE		2
# define CANNOT_EXEC_CMD	126
# define CMD_NOT_FOUND		127
# define INVALID_EXIT_ARG	128
# define TERMINATE_CTRL_C	130
# define TERMINATE_QUIT		131
# define OUT_OF_RANGE		255

/* utils.c */

void	terminate(char *s, int syserr);
int		free_and_return_error_code(char **str, int err);

/* exec_utils.c */
char	**get_command_array(t_list *command);
char	**get_envp(t_list *environ);
int		handle_child_exit(int exit_status, int last_pipe_exit, int last_pipe);

/* split_utils.c */

void	find_closing_quote(char *line, int *i, int *quote_flag, char quote);
int		count_splits(char **split_line);
void	move_to_end_of_quote(char *line, int *i);
void	set_split(char ***split_line, t_split_data *split, char *line, int i);

/* split_utils_2.c */

int		print_error_syntax(const char *token);
int		syntax_error(char *word);
void	set_opposite_binary(int *value);

/* expand_words_utils.c */

void	copy_char_to_word(char *word, char *cpy_word,
			int *from_index, int *to_index);
int		new_word_length(char *word, int exit_status);
#endif