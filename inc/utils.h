/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:58:30 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/07 11:10:31 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define ERR_ARGS			"Incorrect number of arguments, expected 0"
# define ERR_QUOTES			"Opening quotes aren't properly closed"
# define ERR_SYNTAX			"-msh: Syntax error near unexpected token"
# define ERR_GETPWD			"Function error -> getpwd"
# define ERR_MEM			"Fuction error -> malloc"
# define ERR_SIG			"Function error -> sigaction"
# define ERR_TC_GET_ATTR	"Function error -> tcgetattr"
# define ERR_SIGADDSET		"Function error -> sigaddset"
# define ERR_FORK			"Function error -> fork"
# define ERR_WAIT			"Function error -> wait"
# define ERR_EXECVE			"Function error -> execve"

/* utils.c */

void	terminate(char *s, int system_error_flag);
void	init_shell(void);
int		free_and_return_error_code(char **str, int err);
void	ft_free_twod_memory(char **arr);

/* split_utils.c */

typedef struct s_split_data
{
	int	start;
	int	end;
	int	num;
}		t_split_data;

void	find_closing_quote(char *line, int *i, int *quote_flag, char quote);
int		count_splits(char **split_line);
void	move_to_end_of_quote(char *line, int *i);
void	set_split(char ***split_line, t_split_data *split, char *line, int i);

/* split_utils_2.c */

int		print_error_syntax(const char *token);
int		syntax_error(char *word);
void	set_opposite_binary(int *value);
void	copy_char_to_word(char *word, char *cpy_word, int *from_index, int *to_index);

#endif
