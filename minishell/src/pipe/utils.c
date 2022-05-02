/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:20:41 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/02 08:13:07 by jmartin          ###   ########.fr       */
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
	while (++i < shell->cmd_count - 1)
	{
		pipe(fd);
		shell->cmd[i]->out = fd[1];
		if (i == 0)
			shell->cmd[i]->in = fd[0];
		else
			shell->cmd[i + 1]->in = fd[0];
		ft_printf("%d <- out - in -> %d\n", shell->cmd[i]->out, shell->cmd[i]->in);
		close(fd[0]);
		close(fd[1]);
	}
}
