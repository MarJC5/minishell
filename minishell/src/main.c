/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:53:58 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/30 10:32:03 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	run_cmd(t_shell *shell, char *cmd)
{
	if (cmd)
	{
		if (str_cmd_comp(cmd, "unset"))
			unset(shell);
		else if (str_cmd_comp(cmd, "export"))
			export(shell);
		else if (str_cmd_comp(cmd, "pwd"))
			pwd(shell);
		else if (str_cmd_comp(cmd, "env"))
			env(shell);
		else if (str_cmd_comp(cmd, "cd"))
			ft_cd(shell);
		else if (str_cmd_comp(cmd, "echo"))
			ft_echo(shell);
		else
			str_err("minishell: command not found: ", shell->cmd->name);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*line;

	(void) argc;
	(void) argv;
	ascii_prompt();
	shell = malloc(sizeof(t_shell));
	set_envp(shell, envp);
	init_signals();
	line = init_read(shell);
	while (line)
	{
		add_history(line);
		run_cmd(shell, init_cmd(shell, line));
		ft_free_read_args(shell, line);
		line = init_read(shell);
	}
	free(shell);
	return (0);
}
