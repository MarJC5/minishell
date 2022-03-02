/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaquier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:10:48 by tpaquier          #+#    #+#             */
/*   Updated: 2021/10/20 09:13:19 by tpaquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*mem;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (start > ft_strlen(s)) //ce que j'ai rajouté ce if
		len = 0;
	if (start == (ft_strlen(s) - 1))
		len = 1;
	mem = malloc(sizeof(char) * len + 1);
	if (!mem)
		return (NULL);
	while (i < len && start < ft_strlen(s))
		mem[i++] = s[start++];
	mem[i] = '\0';
	return (mem);
}