/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:49:39 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/01/11 18:01:42 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new;
	ssize_t	i;
	ssize_t	j;
	ssize_t	len;

	if (!s1)
	{
		s1 = ft_strdup("\0");
		if (!s1)
			return (NULL);
	}
	len = ft_strlen(s1) + ft_strlen(s2);
	new = (char *)ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		new[i] = s1[i];
	while (s2[++j])
		new[i + j] = s2[j];
	return (new);
}