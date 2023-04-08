/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mnshll_words.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:12:50 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/08 18:15:54 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNSHLL_WORDS_H
# define MNSHLL_WORDS_H

# include "libft.h"
# include "ft_printf_fd.h"

# include "mnshll_data.h"

// Tokenizer Function Bellow
//
// Word Split
int		split_words(t_prompt *prompt);

// Word Split Tools
void	handle_redirection_split(char *split_cmd, t_list **token,
			enum e_type *last_word_type, t_cmdline *cmdline);
void	set_token_node(char *word, t_list **token, enum e_type *last_word_type);
void	set_word_type(char *word, size_t word_len, enum e_type *last_word_type);
void	add_new_word(char *split_cmd, t_word *word, t_list **token,
			t_cmdline *cmdline);

// Word Split Utils
int		check_syntax_error(t_list **cmdline);
t_bool	redirection_conditions(char *split_cmd);
void	init_word(t_word *word, enum e_type *last_word_type);
t_bool	is_single_redirection(char *split_cmd, int word_end);
t_bool	is_double_redirection(char *split_cmd, int word_end);

#endif