/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 10:52:05 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/20 16:41:32 by jmartin          ###   ########.fr       */
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

char	*append_last(char *str, char after)
{
	char	*ret;
	size_t	len;

	ret = NULL;
	len = ft_strlen(str);
	if (after)
	{
		ret = malloc(sizeof(char) * (len + 2));
		ft_memcpy(ret, str, len);
		ret[len] = after;
		ret[len + 1] = '\0';
		ft_free_tab(str);
	}
	return (ret);
}

int	str_err(char *str, char *err)
{
	char	*msg;

	g_exit_stat = 1;
	if (str && err)
	{
		msg = ft_strjoin(str, err);
		ft_putstr_fd(msg, 2);
		free(msg);
	}
	else if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (EXIT_FAILURE);
}

int	str_perr(char *name, char *arg)
{
	char	*msg;

	g_exit_stat = 1;
	msg = ft_strjoin(name, arg);
	perror(msg);
	free(msg);
	return (EXIT_FAILURE);
}
