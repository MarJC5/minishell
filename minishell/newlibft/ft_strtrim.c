/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaquier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:09:23 by tpaquier          #+#    #+#             */
/*   Updated: 2021/10/20 09:14:24 by tpaquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_strtrim_count(char c, const char *s)
{
	size_t	g;

	g = 0;
	while (s[g])
	{
		if (s[g] == c)
			return (0);
		g++;
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	c;

	i = 0;
	c = ft_strlen(s1);
	while (s1[i] && ft_strtrim_count(s1[i], set) == 0)
		i++;
	while (c > i && ft_strtrim_count(s1[c - 1], set) == 0)
		c--;
	return (ft_substr(s1, i, (c - i)));
}
