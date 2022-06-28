/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:57:16 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/28 19:53:59 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strchr_env(char *str, char c)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	ret = malloc(sizeof(char) * i + 1);
	if (!ret)
		return (NULL);
	j = 0;
	while (j < i)
	{
		ret[j] = str[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*ft_strchr_no_delimiter(const char *s, int c)
{
	int	i;

	i = 0;
	if (c == '\0')
	{
		s += ft_strlen(s);
		return ((char *)s);
	}
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)&s[i] + 1);
		i++;
	}
	return (NULL);
}

int	ft_while_for_rien(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '/' || str[i] == ' '
			|| str[i] == '\0' || str[i] == '\'')
			return (i);
		if (str[i + 1] && str[i + 1] == '$')
			return (i + 1);
		i++;
	}
	return (i);
}
