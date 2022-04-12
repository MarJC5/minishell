/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:53:58 by jmartin           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/12 01:05:11 by jmartin          ###   ########.fr       */
=======
/*   Updated: 2022/03/21 13:16:45 by jmartin          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	run_cmd(t_shell *shell)
{
	if (shell->cmd_count < 2)
	{
		shell->cmd[0]->func(shell, 0);
		return (EXIT_SUCCESS);
	}
	else if (shell->cmd_count > 1)
		ft_putstr_fd("More cmd has been founded", 1);
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
<<<<<<< HEAD
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			init_cmd(shell, line);
			run_cmd(shell);
			ft_free_read_args(shell, line);
		}
=======
		add_history(line);
		ft_printf("\033[1;33m>\033[0m %s\n", line);
		run_cmd(shell, init_cmd(shell, line));
		ft_free_read_args(shell, line);
>>>>>>> main
		line = init_read(shell);
	}
	free(shell);
	return (0);
}
