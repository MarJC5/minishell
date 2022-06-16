/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 10:52:05 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/16 11:48:33 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	args_counter(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		;
	return (i);
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

int	str_err(char *str, char *err)
{
	char	*msg;

	if (str && err)
	{
		msg = ft_strjoin(str, err);
		ft_putstr_fd(msg, 2);
		free(msg);
	}
	else if (str)
		ft_putstr_fd(str, 2);
	ft_printf("\n");
	return (EXIT_FAILURE);
}

int	str_perr(char *name, char *arg)
{
	char	*msg;

	msg = ft_strjoin(name, arg);
	perror(msg);
	free(msg);
	return (EXIT_FAILURE);
}