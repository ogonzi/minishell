/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mnshll_builtins.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:02:34 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/10 18:13:57 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNSHLL_BUILTINS_H
# define MNSHLL_BUILTINS_H

# define MS_MAX_PATH	(unsigned long)1024
# define MS_PATH		(char *)"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin"
# define MS_PWDCMP		(char *)"PWD="

// Built-In Functions
void	check_ft_builtins(t_prompt *prompt, size_t	ac, char **av, char **ev);
void	ft_pwd(size_t ac, char **ev);

#endif