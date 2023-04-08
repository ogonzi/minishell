/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 16:54:14 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/02/19 20:19:20 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_putnbr_base_fd(t_ll nbr, int base, int fd)
{
	char	*str;

	str = "0123456789abcdef";
	if (nbr < 0)
	{
		if (base <= 10)
		{
			if (write(fd, "-", sizeof(char)) < 0)
				return (-1);
			ft_absval(nbr);
		}
		else
			nbr = ft_stou(nbr);
	}
	if (nbr >= base)
		if (ft_putnbr_base_fd(nbr / base, base, fd) == -1)
			return (-1);
	if (write(fd, &str[nbr % base], sizeof(char)) < 0)
		return (-1);
	return (0);
}
