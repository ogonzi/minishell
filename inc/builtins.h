/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 19:18:30 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/01/18 19:21:34 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "ft_printf_fd.h"

# include <stdio.h>
# include <dirent.h>

# define PWDCMP		(char *)"PWD="
# define OLDPWDCMP	(char *)"OLDPWD="
# define HOMEPWDCMP	(char *)"HOME="

// CD builtin
void	get_pwd(char **pwd, char **ev);
void	get_oldpwd(char **pwd, char **ev);
void	get_homepwd(char **pwd, char **ev);

#endif