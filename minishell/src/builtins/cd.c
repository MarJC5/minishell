/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:47:44 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/20 16:33:48 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_cd(t_shell *shell, int cmd_index)
{
	env_updater(shell, "OLDPWD", getcwd(shell->current_path, 100));
	if (shell->cmd[cmd_index]->args[1] != NULL
		|| shell->cmd[cmd_index]->args_count == 1)
	{
		if (shell->cmd[cmd_index]->args_count == 1)
		{
			g_exit_stat = 0;
			chdir("/");
			env_updater(shell, "PWD", getcwd(shell->current_path, 100));
			ft_printf("%s\n", shell->current_path);
		}
		else
		{
			if (chdir(shell->cmd[cmd_index]->args[1]) == -1)
				str_perr("cd: ", shell->cmd[cmd_index]->args[1]);
			else
			{
				g_exit_stat = 0;
				env_updater(shell, "PWD", getcwd(shell->current_path, 100));
				ft_printf("%s\n", shell->current_path);
			}
		}
	}
}
