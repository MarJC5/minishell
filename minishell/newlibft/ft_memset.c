/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaquier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:01:39 by tpaquier          #+#    #+#             */
/*   Updated: 2021/10/20 14:42:14 by tpaquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*s2;
	size_t			i;

	i = 0;
	s2 = (unsigned char *)b;
	while (len > 0)
	{
		s2[i] = (unsigned char) c;
		i++;
		len--;
	}
	return (s2);
}
