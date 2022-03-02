/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaquier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:00:58 by tpaquier          #+#    #+#             */
/*   Updated: 2021/10/20 09:01:01 by tpaquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	char		*s2;

	s2 = (char *)s;
	i = 0;
	while (i < n)
	{
		if (s2[i] == (char)c)
			return ((char *)s2 + i);
		i++;
	}
	return (NULL);
}
