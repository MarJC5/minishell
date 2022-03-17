/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 10:52:05 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/17 15:01:44 by jmartin          ###   ########.fr       */
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

/**
 * @brief Add char before/after a string
 *
 * @param before
 * @param str
 * @param after
 * @return char*
 */

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

void	ascii_prompt(void)
{
	ft_printf("\n\033[1;32m░█▀▄▀█░░▀░░█▀▀▄░░▀░░█▀▀░█░░░░█▀▀░█░░█░\n");
	ft_printf("░█░▀░█░░█▀░█░▒█░░█▀░▀▀▄░█▀▀█░█▀▀░█░░█░\n");
	ft_printf("░▀░░▒▀░▀▀▀░▀░░▀░▀▀▀░▀▀▀░▀░░▀░▀▀▀░▀▀░▀▀\n");
	ft_printf("\033[0;32mby Tpaquier & Jmartin                   \033[0m\n\n");
}
