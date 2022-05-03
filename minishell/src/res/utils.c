/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 10:52:05 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/03 19:26:51 by jmartin          ###   ########.fr       */
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

int	str_cmd_comp(char *cmd, char *comp)
{
	char	*str_upper;
	int		i;

	i = -1;
	str_upper = ft_strdup(comp);
	while (comp[++i])
		str_upper[i] = ft_toupper(comp[i]);
	if (ft_strcmp(cmd, comp) == 0
		|| ft_strcmp(cmd, str_upper) == 0)
	{
		free(str_upper);
		return (1);
	}
	free(str_upper);
	return (0);
}
