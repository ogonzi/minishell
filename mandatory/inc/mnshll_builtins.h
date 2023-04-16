/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mnshll_builtins.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:02:34 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/16 16:04:37 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNSHLL_BUILTINS_H
# define MNSHLL_BUILTINS_H

# include "mnshll_data.h"
# include "dirent.h"

# define MS_MAX_PATH	(unsigned long)1024
# define MS_PATH		(char *)"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin"
# define MS_PWDCMP		(char *)"PWD="
# define MS_ENVCMP		(char *)"env"
# define MS_FLGCMP		(char *)"-n"
# define MS_EXPCMP		(char *)"=\"\""

typedef struct s_cd_vals
{
	char			**segments;
	int				idx;
	DIR				*dp;
	struct dirent	*dirpwd;
	char			*pwd;
}t_cd_vals;

// Built-In Functions
int		check_ft_builtins1(t_prompt *prompt, char **av, char **ev);
int		check_ft_builtins2(t_prompt *prompt, t_pipe pipe_helper,
			char **av, char **ev);
int		ft_builtins(t_prompt *prompt, size_t ac, char **av, char **ev);

// PWD Built-In Function
int		ft_pwd(size_t ac, t_prompt *prompt);

// ENV Built-In Function
int		ft_env(int ac, char **av, char **ev);

// EXIT Built-In Function
void	ft_exit(int ac, char **av);

// ECHO Built-In Function
int		ft_echo(int ac, char **ev);

// EXPORT Built-In Function
int		ft_export(int ac, char **av, t_prompt *prompt);

// EXPORT Utils Built-In Function
void	before_export(t_env **env, char *data, t_bool flag);
void	mns_export(t_env **env, t_bool flag, char **str);
void	bubble_sort(char **arr, int size);
char	*aux_print_declare_env_join(t_env *cpy);

// UNSET Built-In Function
int		ft_unset(int ac, char **av, t_prompt *prompt);

// CD Built-In Function
int		ft_cd(int ac, char **av, t_prompt *prompt);
int		do_pwd(t_prompt **prompt, char *pwd);

// CD Utils Built-In Functions
void	get_pwd(char **pwd, t_prompt **prompt);
void	get_homepwd(char **pwd, t_prompt **prompt);
void	get_oldpwd(char **pwd, t_prompt **prompt);
int		get_rootpwd(t_prompt **prompt);

// CD Tools Built-In Functions
void	ft_swap_content(char **a, char **b);
void	export_oldpwd(t_env *env);
void	export_pwd(t_env *env);

// CD Auxiliar Built-In Functions
void	before_export_oldpwd(t_prompt **prompt);
void	before_export_pwd(t_prompt **prompt);
void	aux_ft_cd(t_cd_vals *data, t_prompt *prompt);
int		is_valid_path(char *path);
int		check_valid_path(char *path, char *str);

#endif