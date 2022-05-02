/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:20:44 by tpaquier           #+#    #+#             */
/*   Updated: 2022/04/28 07:28:35 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	path_exec(t_shell *shell, int cmd_index)
{
	char		**path;
	pid_t		child_proc;

	path = path_finder(shell);
	child_proc = fork();
	if (child_proc == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_proc == 0)
	{
		open_dir(shell, path, shell->cmd[cmd_index]->name, cmd_index);
		exit(EXIT_FAILURE);
	}
	else
		child_proc = wait(NULL);
	free(path);
}
