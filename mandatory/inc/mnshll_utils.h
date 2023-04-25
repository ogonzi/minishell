/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mnshll_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:53:56 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/25 16:00:35 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNSHLL_UTILS_H
# define MNSHLL_UTILS_H

# include "libft.h"
# include "ft_printf_fd.h"

# include "mnshll_data.h"

// Banner Read
void	read_banner(void);

// Enviroment Utils Functions
void	custom_export(t_env *env, char *data);
char	**ft_split_once(char const *s, char c);
char	*ft_strtrim_charset_end(char *str, char *end);
void	ft_cmdline_clear(t_list **lst, void (*del)(void *));
void	ft_token_clear(t_list **lst, void (*del)(void *));

// List Utils Functions
t_env	*ft_env_iter(t_env *env, char *ref);
size_t	ft_env_size(t_env *env);
void	ft_env_clear(t_env **env, void (*del)(void *));
t_env	*ft_env_last(t_env **env);
void	ft_env_addback(t_env **env, t_env *new);

// Minishell Utils Extra
t_bool	ft_isall_space(char *buf);
void	aux_handler_pipeline(t_prompt *prompt, int tmp_fd[2]);

#endif