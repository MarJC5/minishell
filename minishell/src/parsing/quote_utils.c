/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:14:50 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/21 16:45:04 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	quote_counter(char *s, char c)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] == c)
			j++;
	}
	if (j % 2 != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	*remove_append(char *str, char c)
{
	size_t	i;
	char	*src;
	char	*dst;

	i = 0;
	dst = str;
	src = dst;
	while (*src != '\0')
	{
		*dst = *src;
		if (*dst != c)
			dst++;
		src++;
		i++;
	}
	*dst = '\0';
	return (dst);
}

char	*remove_char(char *str, char c)
{
	char	*src;
	char	*dst;

	dst = str;
	src = dst;
	while (*src != '\0')
	{
		*dst = *src;
		if (*dst != c)
			dst++;
		src++;
	}
	*dst = '\0';
	return (dst);
}

char	*rm_quote_out(char *str, char c)
{
	char	*src;
	char	*dst;
	size_t	i;
	size_t	end;

	dst = str;
	src = dst;
	i = 0;
	end = ft_strlen(str) - 1;
	while (*src != '\0')
	{
		*dst = *src;
		if (*dst != c && (i != 0 || i != end))
			dst++;
		src++;
		i++;
	}
	*dst = '\0';
	return (dst);
}
