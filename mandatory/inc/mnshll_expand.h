/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mnshll_expand.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:15:08 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/20 20:43:58 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNSHLL_EXPAND_H
# define MNSHLL_EXPAND_H

# include "libft.h"
# include "ft_printf_fd.h"

# include "mnshll_data.h"

// Minishell Expander Functions

// ExpanderFunctions
void	expand_words(t_prompt *prompt);
void	handle_word_expansion(char *word, int *single_quoted, t_env *env);
void	expand(char *word, int *remove_char, t_env *env);

// Expander Tools Functions
void	handle_expand_env_var(char *word, ssize_t *idx,
			int *remove_char, t_env *env);
void	remove_quotes(char *word, int *remove_char, int *single_quoted);
void	format_word(char *word, int *remove_char);
char	*expand_env(char *word, int exit_status, t_env *env);

// Expander Util Funtions
int		new_word_length(char *word, int exit_status, t_env *env);
t_bool	get_added_length(char *word, t_expander_wlen *exp_word_len,
			int exit_status, t_env *env);
void	copy_char_to_word(char *word, char *cpy_word,
			int *from_index, int *to_index);
void	set_exit_status_to_word(char *word, int exit_status, int *i, int *j);

// Expander Env Utils Functions
char	*get_env_var(char *word, int *idx, t_env *env);
int		get_env_var_length(char *word, ssize_t *idx, t_env *env);
void	set_new_word(char *word, char *cpy_word, int exit_status, t_env *env);

#endif