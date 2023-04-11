/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mnshll_builtins.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:02:34 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/11 12:58:38 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNSHLL_BUILTINS_H
# define MNSHLL_BUILTINS_H

# define MS_MAX_PATH	(unsigned long)1024
# define MS_PATH		(char *)"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin"
# define MS_PWDCMP		(char *)"PWD="
# define MS_ENVCMP		(char *)"env"
# define MS_FLGCMP		(char *)"-n"

// Built-In Functions
int		check_ft_builtins(t_prompt *prompt, size_t	ac, char **av, char **ev);

int		ft_pwd(size_t ac, char **ev);
int		ft_env(int ac, char **av, char **ev);
void	ft_exit(int ac, char **av);
int		ft_echo(int ac, char **ev);
int		ft_export(int ac, char **av, char **ev, t_prompt *prompt);

#endif