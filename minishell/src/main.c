/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:53:58 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/16 14:32:55 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int run_cmd(t_shell *shell, char *cmd)
{
	if (cmd)
	{
		if (ft_strcmp(cmd, "unset") == 0)
			unset(shell);
		else if (ft_strcmp(cmd, "export") == 0)
			export(shell);
		else if (ft_strcmp(cmd, "pwd") == 0)
			pwd();
		else if (ft_strcmp(cmd, "env") == 0)
			env(shell);
		else
			str_err("minishell: command not found: ", shell->cmd->name);
		ft_free_tab(shell->cmd->name);
		ft_free_multi_tab(shell->cmd->args);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*line;

	shell = malloc(sizeof(t_shell));
	set_envp(shell, envp);
	init_signals();
	line = init_read(shell);
	while (line)
	{
		ft_printf("\033[1;37m>\033[0m %s\n", line);
		if (run_cmd(shell, init_cmd(shell, line)))
			ft_printf("\n", line);
		line = init_read(shell);
	}
	return (0);
}
