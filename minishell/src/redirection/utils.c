/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:45:03 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/31 09:25:40 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	isrediorpipe(t_shell *shell, char **args, char sign)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == sign)
			{
				shell->i = i;
				shell->j = j;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	isdoubleredi(char **args, char sign)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == sign)
			{
				if (args[i][j + 1] == sign)
					return (2);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

char	*getname(char **args, int i, int j)
{
	char	*name;
	int		g;

	g = 0;
	if (args[i][j + 1] && args[i][j + 1] != '>')
		name = malloc(ft_strlen(&args[i][++j]) + 2);
	else if (args[i][j + 1] == '>' && args[i][j + 3])
		name = malloc(ft_strlen(&args[i][j += 2]) + 2);
	else
	{
		if (args[i + 1])
		{
			name = malloc(ft_strlen(args[++i]) + 2);
			j = 0;
		}
		else
			return (NULL);
	}
	name[g++] = '/';
	while (args[i][j])
		name[g++] = args[i][j++];
	name[g] = '\0';
	return (name);
}
