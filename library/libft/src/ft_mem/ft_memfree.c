/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:41:15 by cpeset-c          #+#    #+#             */
/*   Updated: 2022/10/25 14:06:58 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char
	**ft_memfree(char **ptr, int len)
{
	while (len--)
		free(ptr[len]);
	free(ptr);
	ptr = NULL;
	return (NULL);
}
