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
	while (shell->cmd[cmd_index]->args[j])
	{
		write(1, shell->cmd[cmd_index]->args[j],
			ft_strlen(shell->cmd[cmd_index]->args[j]));
		if (++j != shell->cmd[cmd_index]->args_count)
			write(1, " ", 1);
	}
}

void	ft_echo(t_shell *shell, int cmd_index)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	if (ft_strcmp(shell->cmd[cmd_index]->args[1], "-n") == 0)
		j = 2;
	else
		i = 1;
	if (shell->cmd[cmd_index]->args[i])
	{
		echo_write(shell, cmd_index, j);
		if (i == 1)
			write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
}
