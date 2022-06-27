/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:53:58 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/14 11:10:24 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_struct(t_shell *shell)
{
	shell->ispipe = 0;
	shell->bcklash_n = 0;
	shell->redi = 0;
	shell->i = 0;
	shell->j = 0;
	shell->heredoc = 0;
	shell->env_size = 0;
	shell->fd = 0;
	shell->cmd_count = 0;
	shell->out_status = 0;
	shell->in_status = 0;
	shell->exit_status = 0;
}

int	run_cmd(t_shell *shell)
{
	if (shell->cmd_count == 1 && !shell->ispipe)
	{
		if (shell->redinput)
			old_fd(shell, 2);
		else if (shell->redi >= 1)
			old_fd(shell, 1);
		else
			shell->cmd[0]->func(shell, 0);
		shell->redi = 0;
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
	struct termios	saved;
	t_shell			*shell;

	(void) argc;
	(void) argv;
	ascii_prompt();
	shell = malloc(sizeof(t_shell));
	set_envp(shell, envp);
	init_signals(&saved);
	shell->line = init_read(shell);
	while (shell->line)
	{
		ft_struct(shell);
		if (ft_isspace(shell->line))
		{
			init_cmd(shell, ft_strdup(shell->line));
			run_cmd(shell);
			add_history(shell->line);
			ft_free_read_args(shell, shell->line);
		}
		shell->line = init_read(shell);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	free(shell);
	return (0);
}
