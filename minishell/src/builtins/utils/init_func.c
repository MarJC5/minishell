/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 00:43:58 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/03 14:30:05 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	init_func(t_shell *shell, int i)
{
	if (str_cmd_comp(shell->cmd[i]->name, "unset"))
		shell->cmd[i]->func = unset;
	else if (str_cmd_comp(shell->cmd[i]->name, "export"))
		shell->cmd[i]->func = export;
	else if (str_cmd_comp(shell->cmd[i]->name, "pwd"))
		shell->cmd[i]->func = pwd;
	else if (str_cmd_comp(shell->cmd[i]->name, "env"))
		shell->cmd[i]->func = env;
	else if (str_cmd_comp(shell->cmd[i]->name, "cd"))
		shell->cmd[i]->func = ft_cd;
	else if (str_cmd_comp(shell->cmd[i]->name, "echo"))
		shell->cmd[i]->func = ft_echo;
	else if (str_cmd_comp(shell->cmd[i]->name, "exit"))
		shell->cmd[i]->func = ft_exit;
	else if (dir_exist(shell, shell->cmd[0]->name) == 1)
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
