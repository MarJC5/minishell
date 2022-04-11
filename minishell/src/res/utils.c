/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 10:52:05 by jmartin           #+#    #+#             */
/*   Updated: 2022/04/11 15:10:32 by jmartin          ###   ########.fr       */
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

void	str_err(char *str, char *err)
{
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(err, 2);
	}
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
		|| ft_strcmp(cmd, str_upper) == 0 )
	{
		free(str_upper);
		return (1);
	}
	free(str_upper);
	return (0);
}

void	ascii_prompt(void)
{
	ft_printf("\n\033[1;32m░█▀▄▀█░░▀░░█▀▀▄░░▀░░█▀▀░█░░░░█▀▀░█░░█░\n");
	ft_printf("░█░▀░█░░█▀░█░▒█░░█▀░▀▀▄░█▀▀█░█▀▀░█░░█░\n");
	ft_printf("░▀░░▒▀░▀▀▀░▀░░▀░▀▀▀░▀▀▀░▀░░▀░▀▀▀░▀▀░▀▀\n");
	ft_printf("\033[0;32mby Tpaquier & Jmartin                   \033[0m\n\n");
}
