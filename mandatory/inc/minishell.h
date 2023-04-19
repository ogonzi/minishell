/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:37:32 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/19 20:18:32 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "ft_printf_fd.h"

# include "mnshll_data.h"

// Promopt
void	init_prompt(t_prompt *prompt, char **av, char **ev);

// Init Prompt Functions
void	custom_getpid(t_prompt *prompt);
void	set_environ(t_env **env, char **ev);
void	set_custom_env(t_env **env, char *prog);
void	custom_void_env(t_env **env, char *prog);
char	*get_custom_pwd(void);
char	*check_string(char *str);

// Signal Functions
void	set_sigint_action(void);
void	set_child_sigaction(void);
void	do_sigign(int signum);
void	set_sigint_action_heredoc(void);

#endif