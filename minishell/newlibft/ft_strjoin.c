/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaquier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:03:16 by tpaquier          #+#    #+#             */
/*   Updated: 2021/10/20 09:03:18 by tpaquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		prefix;
	int		suffix;
	int		full;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	prefix = ft_strlen(s1);
	suffix = ft_strlen(s2);
	full = prefix + suffix;
	str = malloc((prefix + suffix + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (s1 && s2)
	{
		ft_memcpy(str, s1, prefix);
		ft_memcpy(str + prefix, s2, suffix);
	}
	str[full] = '\0';
	return ((char *)str);
}
