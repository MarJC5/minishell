/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:22:06 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/03 15:42:12 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' '
			|| str[i] == '\f'
			|| str[i] == '\n'
			|| str[i] == '\r'
			|| str[i] == '\t'
			|| str[i] == '\v')
			i++;
		else
			return (1);
	}
	return (0);
}

void	exit_status(int wstatus)
{
	if (WIFEXITED(wstatus))
		g_exit_stat = WEXITSTATUS(wstatus);
}
