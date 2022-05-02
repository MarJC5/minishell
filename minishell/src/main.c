/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:53:58 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/02 22:05:35 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	run_cmd(t_shell *shell)
{
	if (shell->cmd_count == 1 && !shell->ispipe)
	{
		shell->cmd[0]->func(shell, 0);
		return (EXIT_SUCCESS);
	}
	else if (shell->cmd_count >= 1 && shell->ispipe > shell->cmd_count)
		str_err("minishell: syntax error near unexpected token `|'",
			NULL);
	else if (shell->cmd_count > 1)
		pipex(shell);
	return (EXIT_FAILURE);
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
		if (ft_isspace(line))
		{
			add_history(line);
			init_cmd(shell, line);
			run_cmd(shell);
		}
		ft_free_read_args(shell, line);
		line = init_read(shell);
	}
	ft_free_read_args(shell, line);
	free(shell);
	return (0);
}
