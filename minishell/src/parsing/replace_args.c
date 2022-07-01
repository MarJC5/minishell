/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 00:32:37 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/30 11:54:30 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_replace_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c)
	{
		if (str[i] == '|')
			str[i] = 27;
		else if (str[i] == '<')
			str[i] = 6;
		else if (str[i] == '>')
			str[i] = 11;
		i++;
	}
}

void	replace_dolls_quote(char *args, int i)
{
	char	save;

	save = args[i];
	i++;
	while (args[i] && args[i] != save)
	{
		if (args[i] == '$')
			args[i] = 8;
		i++;
	}
}

void	replace_spec_char(char *args, int i, int count, char save)
{
	while (args[i])
	{
		if ((args[i] == '\'' || args[i] == '\"'))
		{
			if (save == '\0')
				save = args[i];
			if (save == args[i])
			{
				count++;
				if (count >= 2)
				{
					save = '\0';
					count = 0;
				}
				else if (args[i] == '\'' && save != '\"')
					replace_dolls_quote(args, i);
			}
		}
		if (save != '\0')
			ft_replace_char(&args[i], save);
		i++;
	}
}
