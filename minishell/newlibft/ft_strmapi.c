/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaquier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:03:55 by tpaquier          #+#    #+#             */
/*   Updated: 2021/10/20 09:06:25 by tpaquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t		i;
	char		*mem;

	i = 0;
	mem = ft_strdup(s);
	if (!mem || !s || !f)
		return (NULL);
	while (mem[i])
	{
		mem[i] = (*f)(i, mem[i]);
		i++;
	}
	return (mem);
}
