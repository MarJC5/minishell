/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:53:58 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/17 20:58:53 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	run_cmd(t_shell *shell, char *cmd)
{
	if (cmd)
	{
		if (ft_strcmp(cmd, "unset") == 0)
			unset(shell);
		else if (ft_strcmp(cmd, "export") == 0)
			export(shell);
		else if (ft_strcmp(cmd, "pwd") == 0)
			pwd(shell);
		else if (ft_strcmp(cmd, "env") == 0)
			env(shell);
		else
			str_err("minishell: command not found: ", shell->cmd->name);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	t_shell	*shell;
	char	*line;

	ascii_prompt();
	shell = malloc(sizeof(t_shell));
	set_envp(shell, envp);
	init_signals();
	line = init_read();
	while (line)
	{
		add_history(line);
		ft_printf("\033[1;37m>\033[0m %s\n", line);
		if (run_cmd(shell, init_cmd(shell, line)))
			ft_printf("\n", line);
		ft_free_read_args(shell, line);
		line = init_read();
	}
	free(shell);
	return (0);
}
