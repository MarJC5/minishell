/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:20:44 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/02 08:10:58 by jmartin          ###   ########.fr       */
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
	close_loop(shell);
	path_exec(shell, cmd_index);
	exit(EXIT_SUCCESS);
}

void	pipex(t_shell *shell)
{
	/*pid_t	pid1;
	pid_t	pid2;
	int		i;

	i = -1;*/
	init_fd(shell);
	close_loop(shell);
	/* pid1 = fork();
	if (pid1 == -1)
		perror("Pid error");
	if (pid1 == 0)
		dup2(shell->cmd[i]->out, STDOUT_FILENO);
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(shell->cmd[i + 1]->in, STDIN_FILENO);
		child_process(shell, i + 1);
	}
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0); */
}
