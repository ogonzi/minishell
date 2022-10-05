/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:53:26 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/05 17:35:28 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	terminate(char *s, int system_error_flag)
{
	if (system_error_flag == 1)
		perror(s);
	else
		ft_putendl_fd(s, 2);
	exit(EXIT_FAILURE);
}
