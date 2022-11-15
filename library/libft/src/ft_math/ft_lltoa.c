/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:03:21 by cpeset-c          #+#    #+#             */
/*   Updated: 2022/10/24 11:12:19 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_lltoa(t_ll nbr, int base, char *str)
{
	char	*res;
	t_unt	len;

	res = NULL;
	len = ft_nbrlen_base(nbr, base);
	res = (char *)ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (nbr < 0)
		res[0] = '-';
	else if (nbr == 0)
		res[0] = '0';
	while (nbr)
	{
		--len;
		res[len] = str[ft_absval(nbr % base)];
		nbr /= base;
	}
	return (res);
}
