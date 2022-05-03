/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:47:44 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/03 14:39:48 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_cd(t_shell *shell, int cmd_index)
{
	int	i;

	i = 0;
	g_exit_stat = 0;
	while (shell->cmd[cmd_index]->args[i])
	{
		if (shell->cmd[cmd_index]->args[i][0] == 'c'
			&& shell->cmd[cmd_index]->args[i][1] == 'd'
			&& shell->cmd[cmd_index]->args[i][2] == '\0')
			break ;
		i++;
	}
	i++;
	if (chdir(shell->cmd[cmd_index]->args[i]) == -1)
	{
		g_exit_stat = 1;
		str_err("cd: ", shell->cmd[cmd_index]->args[i]);
	}
	else
		chdir(shell->cmd[cmd_index]->args[i]);
	ft_printf("%s\n", getcwd(shell->current_path, 100));
}
