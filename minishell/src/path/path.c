/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:20:44 by tpaquier          #+#    #+#             */
/*   Updated: 2022/06/08 12:52:52 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void check_access(t_shell *shell, int cmd_index)
{
	if (access(shell->cmd[cmd_index]->name,(X_OK)) != 0)
		str_perr(NULL, shell->cmd[cmd_index]->name);
	else if (access(shell->cmd[cmd_index]->name, (X_OK)) == 0)
		g_exit_stat = execve(shell->cmd[cmd_index]->name, shell->cmd[cmd_index]->args,
							 shell->envp);
}

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
		if (ft_strchr(shell->cmd[cmd_index]->name, '/') == NULL)
			open_dir(shell, path,
					 shell->cmd[cmd_index]->name, cmd_index);
		else
			check_access(shell, cmd_index);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(child_proc, NULL, 0);
	ft_free_multi_tab(path);
}
