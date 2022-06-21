/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 00:43:58 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/13 21:06:17 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	init_func(t_shell *shell, int i)
{
	if (ft_strcmp(shell->cmd[i]->name, "unset") == 0)
		shell->cmd[i]->func = unset;
	else if (ft_strcmp(shell->cmd[i]->name, "export") == 0)
		shell->cmd[i]->func = export;
	else if (ft_strcmp(shell->cmd[i]->name, "pwd") == 0)
		shell->cmd[i]->func = pwd;
	else if (ft_strcmp(shell->cmd[i]->name, "env") == 0)
		shell->cmd[i]->func = env;
	else if (ft_strcmp(shell->cmd[i]->name, "cd") == 0)
		shell->cmd[i]->func = ft_cd;
	else if (ft_strcmp(shell->cmd[i]->name, "echo") == 0)
		shell->cmd[i]->func = ft_echo;
	else if (ft_strcmp(shell->cmd[i]->name, "exit") == 0)
		shell->cmd[i]->func = ft_exit;
	else if (dir_exist(shell, i) == 1)
		shell->cmd[i]->func = path_exec;
	else
		shell->cmd[i]->func = builtin_error;
}

void	builtin_error(t_shell *shell, int cmd_index)
{
	g_exit_stat = 127;
	str_err("minishell: command not found: ",
		shell->cmd[cmd_index]->name);
}
