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

int	path_exist(char **env, char *str)
{
	int		i;

	i = 0;
	if (access(str, (X_OK)) == 0)
		return (2);
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			return (0);
		i++;
	}
	g_exit_stat = 127;
	return (1);
}

void	check_access(t_shell *shell, int cmd_index)
{
	g_exit_stat = shell->exit_status;
	if (access(shell->cmd[cmd_index]->name, (X_OK)) == 0)
		execve(shell->cmd[cmd_index]->name,
			shell->cmd[cmd_index]->args, shell->envp);
	else
		shell->cmd[cmd_index]->func(shell, cmd_index);
}

void	path_exec(t_shell *shell, int cmd_index)
{
	pid_t		child_proc;

	if (shell->cmd[cmd_index]->pid == -1)
	{
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
		{
			g_exit_stat = -1;
			waitpid(shell->cmd[cmd_index]->pid, &shell->exit_status, 0);
			exit_status(shell->exit_status);
		}
	}
}
