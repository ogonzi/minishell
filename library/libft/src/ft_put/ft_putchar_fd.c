/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 16:53:52 by cpeset-c          #+#    #+#             */
/*   Updated: 2022/10/07 05:59:31 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int
	ft_putchar_fd(int c, int fd)
{
	if (write(fd, &c, sizeof(char)) != sizeof(char))
		return (-1);
	return (1);
}
