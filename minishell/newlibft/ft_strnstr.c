/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaquier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:06:43 by tpaquier          #+#    #+#             */
/*   Updated: 2021/10/21 14:56:10 by tpaquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	j;
	size_t	g;

	j = 0;
	g = 0;
	if (ft_strlen(n) == 0)
		return ((char *)h);
	while (h[j] && j < len)
	{
		g = 0;
		while (n[g] && g + j < len && h[j + g] == n[g])
			g++;
		if (!n[g])
			return ((char *)(h + j));
		j++;
	}
	return (NULL);
}
