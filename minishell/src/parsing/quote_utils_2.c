/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 00:14:56 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/28 00:24:20 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	quote_counter_sign(char **args, int i, int j, int c)
{
	char	sign;

	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '\"' || args[i][j] == '\'')
			{
				if (c == 0)
					sign = args[i][j];
				if (sign == args[i][j] && c > 0)
					c = 0;
				else
					c++;
			}
			j++;
		}
		i++;
	}
	if (c != 0)
		return (sign);
	return ('\0');
}

void	quote_finder(t_shell *shell, int cmd_index, int i)
{
	int	j;

	j = 0;
	while (shell->cmd[cmd_index]->args[i][j])
	{
		if (shell->cmd[cmd_index]->args[i][j] == '\"'
			|| shell->cmd[cmd_index]->args[i][j] == '\'')
		{
			shell->sq = shell->cmd[cmd_index]->args[i][j];
			shell->sqj = i; // envoyer j pas i
			return ;
		}
		j++;
	}
	shell->sq = '\0';
}

static void	quote_finder_two_eq(t_shell *shell, char *args, int i)
{
	while (args[i])
	{
		if (args[i] == shell->sq)
		{
			shell->eq = args[i];
			return ;
		}
		i++;
	}
}

void	quote_finder_two(t_shell *shell, char *args, int task)
{
	int	i;

	i = 0;
	if (task == 0)
	{
		while (args[i])
		{
			if (args[i] == shell->sq)
			{
				shell->eq = args[i];
				return ;
			}
			i++;
		}
	}
	else
	{
		i = shell->sqj + 1; // reset sqj a 0 après
		quote_finder_two_eq(shell, args, i);
	}
}
