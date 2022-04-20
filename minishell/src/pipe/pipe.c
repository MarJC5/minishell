/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:20:44 by jmartin           #+#    #+#             */
/*   Updated: 2022/04/20 13:03:56 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pipex(t_shell *shell)
{
	int	i;

	if (shell->cmd[0]->in == -1)
		shell->cmd[i]->in = 0;
	if (shell->cmd[shell->cmd_count]->out == -1)
		shell->cmd[shell->cmd_count]->out = 1;
	init_fd(shell);
	i = -1;
	while (++i < shell->cmd_count)
	{
		if (shell->cmd[i]->in != 0)
			close(shell->cmd[i]->in);
		if (shell->cmd[i]->out != 1)
			close(shell->cmd[i]->out);
		i++;
	}
}
