/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:20:44 by jmartin           #+#    #+#             */
/*   Updated: 2022/04/28 16:42:50 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_loop(t_shell *shell)
{
	int	i;
	i = -1;
	while (++i < shell->cmd_count - 1)
	{
		close(shell->cmd[i]->out);
		close(shell->cmd[i]->in);
	}
}

void	child_process(t_shell *shell, int cmd_index)
{
	ft_printf("CHILD IS RUNNING\n");
	path_exec(shell, cmd_index);
}

void	pipex(t_shell *shell)
{
	pid_t	pid1;
	pid_t	pid2;
	int		i;

	i = -1;
	init_fd(shell);
	while (++i < shell->cmd_count - 1)
	{
		pid1 = fork();
		if (pid1 == -1)
			perror("Pid error");
		if (pid1 == 0)
		{
			dup2(shell->cmd[i]->out, STDOUT_FILENO);
			child_process(shell, i);
		}
		pid2 = fork();
		if (pid2 == 0)
		{
			dup2(shell->cmd[i]->in, STDIN_FILENO);
			child_process(shell, i + 1);
		}
		close_loop(shell);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
}
