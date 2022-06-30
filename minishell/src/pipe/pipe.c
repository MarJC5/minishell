/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:20:44 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/13 08:06:54 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_out(t_shell *shell, int cmd_index)
{
	if (isrediorpipe(shell, cmd_index, '>') == 1)
	{
		redirection(shell, cmd_index);
		return (1);
	}
	if (shell->cmd[cmd_index]->out != -1)
	{
		dup2(shell->cmd[cmd_index]->out, STDOUT_FILENO);
		close(shell->cmd[cmd_index]->out);
	}
	return (-1);
}

int	handle_in(t_shell *shell, int cmd_index)
{
	if (isrediorpipe(shell, cmd_index, '<') == 1)
	{
		if (shell->cmd[cmd_index]->heredoc == 1)
			;
		else
			redirection_input(shell, cmd_index);
		return (1);
	}
	if (shell->cmd[cmd_index]->in != -1)
	{
		dup2(shell->cmd[cmd_index]->in, STDIN_FILENO);
		close(shell->cmd[cmd_index]->in);
	}
	return (-1);
}

void	child_process(t_shell *shell, int cmd_index)
{
	shell->out_status = handle_out(shell, cmd_index);
	shell->in_status = handle_in(shell, cmd_index);
	close_loop(shell);
	check_access(shell, cmd_index);
	g_exit_stat = shell->exit_status;
	exit(EXIT_SUCCESS);
}

static void	ft_norme(t_shell *shell, int *fd, int i)
{
	pipe(fd);
	shell->cmd[i]->out = fd[1];
	shell->cmd[i + 1]->in = fd[0];
}

void	pipex(t_shell *shell)
{
	int		i;
	int		fd[2];

	i = -1;
	while (++i < shell->cmd_count - 1)
		ft_norme(shell, fd, i);
	i = -1;
	while (++i < shell->cmd_count)
	{
		is_heredoc(shell, i);
		shell->cmd[i]->pid = fork();
		if (shell->cmd[i]->pid == 0)
			child_process(shell, i);
		if (shell->cmd[i]->heredoc == 1)
			ft_dup_unlink(shell, i);
	}
	close_loop(shell);
	i = -1;
	while (++i < shell->cmd_count)
	{
		g_exit_stat = -1;
		waitpid(shell->cmd[i]->pid, &shell->exit_status, 0);
		exit_status(shell->exit_status);
	}
}
