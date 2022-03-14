/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 10:52:05 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/14 17:39:10 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	args_counter(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		;
	return (i);
}

void	ft_free_tab(char *ptr)
{
	if (ptr)
		free(ptr);
}

void	ft_free_multi_tab(char **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
		ft_free_tab(ptr[i]);
	if (ptr)
		free(ptr);
}

char	*append(char before, char *str, char after)
{
	size_t	len;

	len = ft_strlen(str);
	if (before)
	{
		ft_memmove(str + 1, str, ++len);
		*str = before;
	}
	if (after)
	{
		str[len] = after;
		str[len + 1] = 0;
	}
	return (str);
}
