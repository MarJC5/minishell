/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:20:44 by tpaquier          #+#    #+#             */
/*   Updated: 2022/06/20 16:40:34 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_access(t_shell *shell, int cmd_index)
{
	if (access(shell->cmd[cmd_index]->name, (X_OK)) != 0)
		str_perr(NULL, shell->cmd[cmd_index]->name);
	else if (access(shell->cmd[cmd_index]->name, (X_OK)) == 0)
		g_exit_stat = execve(shell->cmd[cmd_index]->name,
				shell->cmd[cmd_index]->args, shell->envp);
}

void	path_exec(t_shell *shell, int cmd_index)
{
	pid_t		child_proc;

	child_proc = fork();
	if (child_proc == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_proc == 0)
	{
		check_access(shell, cmd_index);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(child_proc, NULL, 0);
}
