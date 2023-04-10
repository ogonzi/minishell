/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mnshll_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:53:56 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/10 10:44:33 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNSHLL_UTILS_H
# define MNSHLL_UTILS_H

# include "libft.h"
# include "ft_printf_fd.h"

# include "mnshll_data.h"

// Enviroment Utils Functions
void	custom_export(t_env *env, char *data);

// List Utils Functions
t_env	*ft_env_iter(t_env *env, char *ref);
size_t	ft_env_size(t_env *env);
void	ft_env_clear(t_env **env, void (*del)(void *));

void	custom_void_env(t_prompt *prompt, char *prog);

#endif