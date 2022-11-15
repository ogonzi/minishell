/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:05:51 by cpeset-c          #+#    #+#             */
/*   Updated: 2022/10/23 18:27:25 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_unt
	ft_nbrlen_base(t_ll nbr, int base)
{
	t_unt	len;

	len = 0;
	if (nbr <= 0)
		len++;
	while (nbr)
	{
		nbr /= base;
		len++;
	}
	return (len);
}
