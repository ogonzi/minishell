/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mnshll_exec.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:43:14 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/16 16:06:21 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNSHLL_EXEC_H
# define MNSHLL_EXEC_H

# include "libft.h"
# include "ft_printf_fd.h"

# include "mnshll_data.h"

// Minishell Executer Functions

// Executer Functions
int		redir_pipe(t_list *command_cpy, t_prompt *prompt,
			int tmp_fd[2], int is_first);
void	do_execve(t_list *command, t_prompt *prompt,
			int tmp_fd[2], t_pipe pipe_helper);

// Redir-In Executer Functions
t_bool	dup_to_in(int *tmp_fd_in, t_list *command);
t_bool	dup_to_out(int *tmp_fd_out, t_list *command, int *did_out_redirection);

// Executer Util Functions
int		handle_child_exit(int exit_status, int last_pipe_exit, int last_pipe);
void	check_pipe(t_pipe *pipe_helper, int tmp_fd[2]);
char	**copy_env(t_env *env, size_t size);
char	**get_command_array(t_list *command);

// Executer Path Functions
t_bool	get_exec_path(char *token, char **exec_path,
			t_list *command, t_prompt *prompt);
void	ft_get_full_path(char *path, char **full_path,
			char *user_exec_path, char **exec_path);
t_bool	ft_check_access(char **exec_path, char **paths);
#endif