/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaquier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:01:29 by tpaquier          #+#    #+#             */
/*   Updated: 2021/10/20 09:01:30 by tpaquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char		*src2;
	char			*dst2;
	size_t			i;

	src2 = (const char *) src;
	dst2 = (char *) dst;
	i = -1;
	if (!src2 && !dst2)
		return (NULL);
	if (src2 < dst2)
	{
		while ((int)--len >= 0)
			dst2[len] = src2[len];
	}
	else
	{
		while (++i < len)
			dst2[i] = src2[i];
	}
	return (dst);
}
