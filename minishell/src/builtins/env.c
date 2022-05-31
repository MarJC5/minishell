/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:42:05 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/31 07:40:03 by jmartin          ###   ########.fr       */
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
		str_err("env: too many arguments : ", shell->cmd[cmd_index]->args[1]);
	}
	else
	{
		g_exit_stat = 0;
		while (shell->envp[++i])
		{
			ft_printf("%s", shell->envp[i]);
			if (shell->envp[i + 1] != NULL)
				ft_printf("\n");
		}
	}
	ft_printf("\n");
}
