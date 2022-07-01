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
	shell->sqj = 0;
	shell->eqj = 0;
	shell->redinput = NULL;
	shell->env_size = 0;
	shell->fd = -1;
	shell->env_name = NULL;
	shell->err_quote = 0;
	shell->err_pipe = 0;
	shell->ct_dols = 0;
	shell->fd_in = -1;
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
			old_fd_two(shell);
		else if (shell->redi >= 1)
			old_fd(shell);
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

static void	ft_void_arg(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	ascii_prompt();
}

static void	ft_free_main(t_shell *shell)
{
	ft_free_multi_tab(shell->envp);
	ft_free_tab(shell->current_path);
	free(shell);
}

int	main(int argc, char **argv, char **envp)
{
	struct termios	saved;
	t_shell			*shell;

	ft_void_arg(argc, argv);
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
			if (shell->err_quote == 0)
				run_cmd(shell);
			add_history(shell->line);
			ft_free_read_args(shell, shell->line);
		}
		shell->line = init_read(shell);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	ft_free_main(shell);
	return (0);
}
