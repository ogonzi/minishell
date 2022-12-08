/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:53:26 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/08 23:43:05 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_fd.h"
#include "ft_printf.h"
#include "utils.h"
#include <stdio.h>

void	terminate(char *s, int system_error_flag)
{
	if (system_error_flag == 1)
		perror(s);
	else
		ft_printf_fd(STDERR_FILENO, "%s\n", s);
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

int	free_and_return_error_code(char **str, int err)
{
	free(*str);
	*str = NULL;
	return (err);
}

void	ft_free_twod_memory(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}
