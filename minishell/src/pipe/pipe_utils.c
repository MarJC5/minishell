/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:20:41 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/03 19:30:38 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_loop(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < shell->cmd_count)
	{
		if (shell->cmd[i]->out != -1)
			close(shell->cmd[i]->out);
		if (shell->cmd[i]->in != -1)
			close(shell->cmd[i]->in);
	}
}

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
