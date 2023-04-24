/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:58:22 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/24 17:25:11 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ll
	ft_atoll_base(const char *str, char *str_base)
{
	t_ll	res;
	int		neg;
	int		base;

	neg = 1;
	res = 0;
	if (ft_ischrinstr(str_base)
		|| (ft_strlen(str_base) < 2 && ft_strlen(str_base) > 16))
		return (0);
	base = ft_strlen(str_base);
	while (*str && ft_isspace(*str))
		str++;
	if (*str && ft_issign(*str))
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (*str && (ft_isdigit(*str)))
	{
		res = res * base + (*str - 48);
		str++;
	}
	return (res * neg);
}

// static int	ft_get_digit(char c, char *str_base, int base);

// t_ll	ft_atoll_base(const char *str, char *str_base)
// {
//     t_ll res = 0;
//     int neg = 1;
//     int base = (int)ft_strlen(str_base);

//     if (!str || !str_base || base < 2 || base > 16)
//         return 0;

//     while (ft_isspace(*str))
//         str++;

//     if (*str == '-' || *str == '+')
//     {
//         neg = (*str == '-') ? -1 : 1;
//         str++;
//     }

//     while (*str)
//     {
//         int digit = ft_get_digit(*str, str_base, base);

//         if (digit < 0)
//             break;

//         res = res * base + digit;
//         str++;
//     }

//     return res * neg;
// }

// static int ft_get_digit(char c, char *str_base, int base)
// {
//     int i;
//     for (i = 0; i < base; i++)
//     {
//         if (str_base[i] == c)
//             return i;
//     }
//     return -1;
// }
