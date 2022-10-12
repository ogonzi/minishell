/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:36:03 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/12 13:05:58 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//# define _DEFAULT_SOURCE 1

/* signals.c */

void	set_sigint_action(void);
void	set_child_sigaction(void);
void	do_sigign(int signum);

/* exec.c */

void	exec(char ***tokens);

/* get_exec_path.c */

int		get_exec_path(char ***tokens, char **exec_path);

/* split.c */

char	**ft_split_mod(const char *str, const char *sep);

/* remove_char.c */

void	ft_remove_char(char *str, char char_to_remove, int first_and_last);

#endif
