/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 19:17:55 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/01/18 20:29:10 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	get_pwd(char **pwd, char **ev)
{
	ssize_t	idx;
	ssize_t	count;

	idx = -1;
	count = ft_strlen(PWDCMP);
	while (ev[++idx])
	{
		if (!ft_strncmp(ev[idx], PWDCMP, count))
		{
			while (count--)
				ev[idx]++;
			*pwd = ev[idx];
			return ;
		}
	}
}

void	get_oldpwd(char **pwd, char **ev)
{
	ssize_t	idx;
	ssize_t	count;

	idx = -1;
	count = ft_strlen(OLDPWDCMP);
	while (ev[++idx])
	{
		if (!ft_strncmp(ev[idx], OLDPWDCMP, count))
		{
			while (count--)
				ev[idx]++;
			*pwd = ev[idx];
			printf("%s\n", *pwd);
			return ;
		}
	}
}

void	get_homepwd(char **pwd, char **ev)
{
	ssize_t	idx;
	ssize_t	count;

	idx = -1;
	count = ft_strlen(HOMEPWDCMP);
	while (ev[++idx])
	{
		if (!ft_strncmp(ev[idx], HOMEPWDCMP, count))
		{
			while (count--)
				ev[idx]++;
			*pwd = ev[idx];
			return ;
		}
	}
}

