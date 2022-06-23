/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:47:54 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/16 09:08:04 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	echo_write(t_shell *shell, int cmd_index, int j)
{
	size_t	i;
	size_t	end;

	while (shell->cmd[cmd_index]->args[j]
		&& j < shell->cmd[cmd_index]->args_count)
	{
		i = 0;
		end = ft_strlen(shell->cmd[cmd_index]->args[j]);
		while (i < end)
		{
			if (shell->cmd[cmd_index]->args[j][i] == ' '
				&& i == 0)
				i++;
			if (shell->cmd[cmd_index]->args[j][i] != '\"'
				&& (i != 0 || i != end))
				write(1, &shell->cmd[cmd_index]->args[j][i], 1);
			i++;
		}
		if (++j != shell->cmd[cmd_index]->args_count
			&& shell->cmd[cmd_index]->quotted == 0)
			write(1, " ", 1);
	}
}

void	ft_echo(t_shell *shell, int cmd_index)
{
	int		i;
	int		start;

	if (ft_strchr(shell->cmd[cmd_index]->args[0], '-') == NULL)
		start = 1;
	else
		start = 0;
	pars_echo_endl(shell, shell->cmd[cmd_index]->args, cmd_index, start);
	if (shell->cmd[cmd_index]->args[start])
	{
		if (shell->bcklash_n)
		{
			i = 2;
			start += 1;
		}
		else
			i = 1;
		echo_write(shell, cmd_index, start);
		if (i == 1)
			write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
}
