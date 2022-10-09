/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:53:26 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/09 13:38:50 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "utils.h"
#include <stdio.h>

void	terminate(char *s, int system_error_flag)
{
	if (system_error_flag == 1)
		perror(s);
	else
		ft_putendl_fd(s, 2);
	exit(EXIT_FAILURE);
}

void	init_shell(void)
{
	printf("\n\n\n\n*******************************");
	printf("\n\n**PROVISIONAL MINISHELL START**");
	printf("\n\n*******************************");
	printf("\n\nUser is: %s\n", getenv("USER"));
	printf("\n");
}

/*
 * En principi el limit de longitud d'un path en MAC es 1024, hi ha una
 * constant que es diu PATH_MAX que ho hauria d'especificar, pero caldria
 * utilizar limits.h i el mateix getcwd diu que no es gaire bona idea
 * utilitzar-ho.
 */

void	print_dir(void)
{
	char	buf[1024];
	char	*err;

	err = getcwd(buf, sizeof(buf));
	if (err == NULL)
		terminate(ERR_GETPWD, 1);
	ft_printf("\033[0;32m");
	ft_printf("%s@%s", getenv("USER"), getenv("NAME"));
	ft_printf("\033[0m");
	ft_printf(":");
	ft_printf("\033[0;34m");
	ft_printf("%s", buf);
	ft_printf("\033[0m");
}

