/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:20:41 by jmartin           #+#    #+#             */
/*   Updated: 2022/04/28 16:06:30 by jmartin          ###   ########.fr       */
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
	int		(*fd)[2];

	fd = malloc(sizeof(*fd[2] * shell->cmd_count + 1));
	i = -1;
	while (++i < shell->cmd_count - 1)
	{
		if (pipe(fd[i]) == -1)
			perror("Cannot open the pipe");
	}
	i = -1;
	while (++i < shell->cmd_count - 1)
	{
		shell->cmd[i]->out = fd[i][1];
		shell->cmd[i]->in = fd[i - 1][0];
		if (i == 0)
			shell->cmd[i]->out = fd[i][1];
		else if (i == shell->cmd_count - 1)
			shell->cmd[0]->in = fd[shell->cmd_count - 1][0];
	}
}
