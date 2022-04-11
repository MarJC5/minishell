/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:53:58 by jmartin           #+#    #+#             */
/*   Updated: 2022/04/11 15:03:45 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	find_cmd(t_shell *shell, int cmd_index)
{
	if (str_cmd_comp(shell->cmd[cmd_index]->name, "unset"))
		unset(shell, cmd_index);
	else if (str_cmd_comp(shell->cmd[cmd_index]->name, "export"))
		export(shell, cmd_index);
	else if (str_cmd_comp(shell->cmd[cmd_index]->name, "pwd"))
		pwd(shell, cmd_index);
	else if (str_cmd_comp(shell->cmd[cmd_index]->name, "env"))
		env(shell, cmd_index);
	else if (str_cmd_comp(shell->cmd[cmd_index]->name, "cd"))
		ft_cd(shell, cmd_index);
	else if (str_cmd_comp(shell->cmd[cmd_index]->name, "echo"))
		ft_echo(shell, cmd_index);
	else if (str_cmd_comp(shell->cmd[cmd_index]->name, "exit"))
		ft_exit(shell);
	else
		str_err("minishell: command not found: ",
			shell->cmd[cmd_index]->name);
}

int	run_cmd(t_shell *shell)
{
	if (shell->cmd_count < 2)
	{
		find_cmd(shell, 0);
		return (1);
	}
	else if (shell->cmd_count > 1)
		ft_putstr_fd("More cmd has been founded", 1);
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
		init_cmd(shell, line);
		run_cmd(shell);
		ft_free_read_args(shell, line);
		line = init_read(shell);
	}
	free(shell);
	return (0);
}
