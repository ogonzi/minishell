/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:53:48 by cpeset-c          #+#    #+#             */
/*   Updated: 2022/11/02 15:02:21 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_ulltoa(t_ull nbr, int base, char *str)
{
	char	*res;
	t_unt	len;

	res = NULL;
	len = ft_unbrlen(nbr, base);
	res = (char *)ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (nbr == 0)
		res[0] = '0';
	while (nbr)
	{
		--len;
		res[len] = str[ft_absval(nbr % base)];
		nbr /= base;
	}
	return (res);
}
