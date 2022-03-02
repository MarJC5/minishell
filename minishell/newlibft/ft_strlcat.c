/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaquier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:03:26 by tpaquier          #+#    #+#             */
/*   Updated: 2021/10/20 09:03:27 by tpaquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t ds)
{
	size_t	j;
	size_t	i;

	j = 0;
	i = ft_strlen(dst);
	if (i < ds - 1 && ds > 0)
	{
		while (src[j] && i + j < ds - 1)
		{
			dst[i + j] = src[j];
			j++;
		}
		dst[i + j] = '\0';
	}
	if (i >= ds)
		i = ds;
	return (i + ft_strlen(src));
}
