/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:24:23 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/30 15:25:45 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_redo_char3(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (name[i] == 27)
			name[i] = '|';
		else if (name[i] == 6)
			name[i] = '<';
		else if (name[i] == 11)
			name[i] = '>';
		else if (name[i] == 8)
			name[i] = '$';
		i++;
	}
}

int	ft_check_getname(char **args, int i, int j)
{
	if ((ft_strlen(args[i]) - j) >= 3 && (args[i][j + 1] == '>'
		|| args[i][j + 1] == '<'))
		return (1);
	return (0);
}
