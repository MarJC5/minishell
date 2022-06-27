/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_space_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 00:15:53 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/28 00:23:13 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_reset_eq_sq(t_shell *shell)
{
	shell->sq = '\0';
	shell->eq = '\0';
	shell->sqi = 0;
	shell->sqj = 0;
}

static void	ft_counter_space_sq(t_shell *shell, char **args, int *i, int *count)
{
	if (shell->sq != '\0')
	{
		if (shell->sqi == *i)
			quote_finder_two(shell, args[*i], 1);
		else
			quote_finder_two(shell, args[*i], 0);
		if (shell->eq == shell->sq)
		{
			*count = 0;
			shell->sq = '\0';
		}
	}
}

static void	ft_counter_space_find_sq(t_shell *shell, int cmd_index, int *i)
{
	if (shell->sq == '\0')
	{
		quote_finder(shell, cmd_index, *i);
		shell->sqi = *i;
	}
}

int	ft_counter_space(t_shell *shell, char **args, int cmd_index)
{
	int	i;
	int	c;
	int	i2;
	int	count;

	i = 0;
	c = 0;
	count = 0;
	i2 = 0;
	ft_reset_eq_sq(shell);
	while (args[i])
	{
		ft_counter_space_find_sq(shell, cmd_index, &i);
		if (shell->sq != '\0')
			count++;
		if (args[i][0] == ' ' && count == 0)
			;
		else
			c++;
		ft_counter_space_sq(shell, args, &i, &count);
		i++;
		i2++;
	}
	ft_reset_eq_sq(shell);
	return (++c);
}
