/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:20:41 by jmartin           #+#    #+#             */
/*   Updated: 2022/04/11 21:48:04 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	is_pipe(char *line, t_shell *shell)
{
	int	i;
	int	pipe;
	int	redi;

	pipe = 0;
	redi = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
			pipe++;
		if (line[i] == '>')
			redi++;
		i++;
	}
	shell->ispipe = pipe;
	shell->redi = redi;
}

void	init_fd(t_shell *shell)
{
	int		i;
	int		fd[2];

	i = -1;
	while (++i < shell->cmd_count)
	{
		if (pipe(fd) == -1)
			str_err("Error: Pipe not proceeded", NULL);
		if (shell->cmd[i]->out == -1)
			shell->cmd[i]->out = fd[1];
		else
			close(fd[1]);
		if (shell->cmd[i + 1]->in == -1)
			shell->cmd[i + 1]->in = fd[0];
		else
			close(fd[0]);
	}
}
