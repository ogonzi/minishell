/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:37:32 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/09 11:44:00 by cpeset-c         ###   ########.fr       */
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

// Parser Header
# include "mnshll_parser.h"

// Words Header
# include "mnshll_words.h"

// Expander Header
# include "mnshll_expand.h"

// Executer Header
# include "mnshll_exec.h"

// Promopt
void	init_prompt(t_prompt *prompt, char **av, char **ev);

// Init Prompt Functions
void	custom_getpid(t_prompt *prompt);
void	set_environ(t_prompt *prompt, char **ev);
void	set_custom_env(t_prompt *prompt, char *prog);

// Signal Functions
void	set_sigint_action(void);
void	set_child_sigaction(void);
void	do_sigign(int signum);

#endif