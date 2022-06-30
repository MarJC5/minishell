/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_space_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 00:15:53 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/30 15:21:12 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_reset_eq_sq(t_shell *shell)
{
	shell->sq = '\0';
	shell->eq = '\0';
	shell->sqi = 0;
	shell->sqj = 0;
	shell->eqj = 0;
}

int	quote_finder_char_count(t_shell *shell, char **args, int i)
{
	while (args[i][shell->eqj])
	{
		if (args[i][shell->eqj] == '\"'
			|| args[i][shell->eqj] == '\'')
		{
			shell->sq = args[i][shell->eqj];
			shell->sqj = shell->eqj;
			shell->eqj = 0;
			shell->eq = '\0';
			return (1);
		}
		shell->eqj++;
	}
	return (0);
}

int	ft_join_quote_count(t_shell *shell, char **args, int *i)
{
	int		c;
	int		counter;

	c = 0;
	counter = 0;
	while (*i < args_counter(args) - 1 && c == 0)
	{
		quote_finder_two(shell, args[*i], 1);
		if (shell->eq != '\0')
		{
			if (quote_finder_char_count(shell, args, *i) == 0)
			{
				c = 1;
			}
		}
		counter++;
		*i += 1;
	}
	return (counter);
}

static void	ft_counter_space_check(int *i, int *c)
{
	*c += 1;
	*i += 1;
}

int	ft_counter_space(t_shell *shell, char **args, int cmd_index)
{
	int	i;
	int	c;
	int	count;

	i = 0;
	c = 0;
	count = 0;
	ft_reset_eq_sq(shell);
	while (args[i])
	{
		pars_sp_loop_sq(shell, cmd_index, &i, &count);
		if (ft_onlyspace(args[i]) && count == 0)
			i++;
		else
		{
			if (shell->sq == '\0')
				ft_counter_space_check(&i, &c);
			else
				c += ft_join_quote_count(shell, args, &i);
			if (i != args_counter(args) - 1)
				quote_finder_two(shell, args[i], 0);
		}
	}
	ft_reset_eq_sq(shell);
	return (++c);
}
