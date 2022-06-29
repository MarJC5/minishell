/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:42:05 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/20 16:34:17 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	env(t_shell *shell, int cmd_index)
{
	int	i;

	i = -1;
	if (shell->cmd[cmd_index]->args_count > 1)
	{
		g_exit_stat = 1;
		str_err("env: No such file or directory: ",
			shell->cmd[cmd_index]->args[1]);
	}
	else
	{
		g_exit_stat = 0;
		while (shell->envp[++i])
		{
			if (ft_strcmp(ft_strchr(shell->envp[i], '='), "=''") != 0)
			{
				ft_printf("%s", shell->envp[i]);
				ft_printf("\n");
			}
		}
	}
}
