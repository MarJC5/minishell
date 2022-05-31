/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:53:58 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/30 16:27:50 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	run_cmd(t_shell *shell)
{
	if (shell->cmd_count == 1 && !shell->ispipe)
		shell->cmd[0]->func(shell, 0);
	else if (shell->cmd_count >= 1 && shell->ispipe > shell->cmd_count)
	{
		g_exit_stat = 2;
		str_err("minishell: syntax error near unexpected token `|'",
			NULL);
	}
	else if (shell->cmd_count > 1)
		pipex(shell);
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	struct termios	saved;
	t_shell			*shell;
	char			*line;

	(void) argc;
	(void) argv;
	ascii_prompt();
	shell = malloc(sizeof(t_shell));
	set_envp(shell, envp);
	init_signals(&saved);
	line = init_read(shell);
	while (line)
	{
		if (ft_isspace(line))
		{
			init_cmd(shell, line);
			run_cmd(shell);
			add_history(line);
			ft_free_read_args(shell, line);
		}
		line = init_read(shell);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	free(shell);
	return (0);
}
