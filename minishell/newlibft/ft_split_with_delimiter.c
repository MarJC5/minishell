/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_delimiter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:02:31 by tpaquier          #+#    #+#             */
/*   Updated: 2022/04/11 07:35:14 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_split_malloc(char const *s, char c, int start)
{
	char	*str;
	int		c2;
	int		i2;
	int		t;

	t = 0;
	c2 = 0;
	i2 = start;
	while (s[start] != c && s[start])
	{
		c2++;
		start++;
	}
	str = (char *)malloc(sizeof(char) * (c2 + 1));
	if (str == NULL)
		return (NULL);
	while (s[i2] != c && s[i2])
	{
		str[t] = s[i2];
		t++;
		i2++;
	}
	str[c2] = '\0';
	return (str);
}

static	int	ft_split_count(char const *s, char c)
{
	size_t	x;
	int		w;

	w = 0;
	x = 0;
	while (x < ft_strlen(s))
	{
		if (s[x] != c && s[x])
		{
			w += 2;
			while (s[x] != c && s[x])
				x++;
		}
		x++;
	}
	return (w);
}

static	int	ft_split_i(char const *s, char c, int i)
{
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static	void	*ft_split_free(char **mem, int j)
{
	while (mem[j] != 0)
		free(mem[j--]);
	free(mem);
	return (NULL);
}

static char	*ft_split_malloc_del(char const *s, char c, int i)
{
	int		start;
	int		x;
	int		x2;
	char	*str;

	start = 0;
	x = 0;
	x2 = i;
	while (s[i++] == c)
		start++;
	str = malloc(start + 1);
	if (!str)
		return (NULL);
	while (start-- != 0)
		str[x++] = s[x2++];
	str[x] = '\0';
	return (str);
}

char	**ft_split_with_delimiter(char const *s, char c)
{
	char	**mem;
	int		j;
	int		i;

	i = 0;
	j = 0;
	mem = (char **)malloc(sizeof(char *) * (ft_split_count(s, c) + 1));
	if (mem == NULL)
		return (NULL);
	while (j < ft_split_count(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		mem[j] = ft_split_malloc(s, c, i);
		if (mem[j] == NULL)
			return (ft_split_free(mem, j));
		j++;
		i = ft_split_i(s, c, i);
		if (s[i] == c)
		{
			mem[j] = ft_split_malloc_del(s, c, i);
			j++;
		}
	}
	mem[j] = NULL;
	return (mem);
}
