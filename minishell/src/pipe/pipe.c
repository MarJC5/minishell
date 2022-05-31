/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:20:44 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/03 19:30:33 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_out(t_shell *shell, int cmd_index)
{
	if (shell->cmd[cmd_index]->out != -1)
	{
		dup2(shell->cmd[cmd_index]->out, STDOUT_FILENO);
		close(shell->cmd[cmd_index]->out);
	}
	return (-1);
}

int	handle_in(t_shell *shell, int cmd_index)
{
	if (isrediorpipe(shell, shell->cmd[cmd_index]->args, '<') == 1)
	{
		shell->cmd[cmd_index]->in = open(shell->cmd[cmd_index]->args[shell->i + 1], O_CREAT | O_RDWR | O_APPEND, 0666);
		printf("%d : fd qu'on cree avec open\n", shell->cmd[cmd_index]->in);
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
	char	**path;

	path = path_finder(shell);
	shell->out_status = handle_out(shell, cmd_index);
	shell->in_status = handle_in(shell, cmd_index);
	printf("%d : valeur de fd\n", shell->cmd[cmd_index]->in);
	printf("%d : valeur de retour de in\n", shell->in_status);
	printf("%d : valeur de retour de out\n", shell->out_status);
	close_loop(shell);
	open_dir(shell, path, shell->cmd[cmd_index]->name, cmd_index);
	free(path);
	exit(EXIT_SUCCESS);
}

void	pipex(t_shell *shell)
{
	int		i;
	int		fd[2];

	i = -1;
	while (++i < shell->cmd_count - 1)
	{
		pipe(fd);
		shell->cmd[i]->out = fd[1];
		shell->cmd[i + 1]->in = fd[0];
	}
	i = -1;
	while (++i < shell->cmd_count)
	{
		shell->cmd[i]->pid = fork();
		if (shell->cmd[i]->pid == 0)
			child_process(shell, i);
	}
	close_loop(shell);
	i = 0;
	while (i < shell->cmd_count)
	{
		waitpid(shell->cmd[i]->pid, &shell->exit_status, 0);
		exit_status(shell->exit_status);
		i++;
	}
}
