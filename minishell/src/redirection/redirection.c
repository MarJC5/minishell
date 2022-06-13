/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:45:11 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/31 10:05:32 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redirection_arg(t_shell *shell, int cmd_index)
{
	int i;
	int	j;

	i = shell->i;
	j = shell->j;
	if (j == 0)
	{
		while (shell->cmd[cmd_index]->args[i])
		{
			free(shell->cmd[cmd_index]->args[i]);
			shell->cmd[cmd_index]->args[i] = NULL;
			i++;
		}
	}
	else
	{
		shell->cmd[cmd_index]->args[i][j] = '\0';
		i++;
		while (shell->cmd[cmd_index]->args[i])
		{
			free(shell->cmd[cmd_index]->args[i]);
			shell->cmd[cmd_index]->args[i] = NULL;
			i++;
		}
	}
}

void	redirection(t_shell *shell, char **args, int cmd_index)
{
	char	*name;
	char	*temp;
	char	cwd[PATH_MAX];

	name = NULL;
	isrediorpipe(shell, args, '>');
	name = getname(args, shell->i, shell->j);
	temp = ft_strjoin(getcwd(cwd, sizeof(cwd)), name);
	free(name);
	name = temp;
	if (isdoubleredi(args, '>') == 2)
		shell->cmd[cmd_index]->out = open(name, O_CREAT | O_RDWR | O_APPEND, 0666);
	else
		shell->cmd[cmd_index]->out = open(name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	dup2(shell->cmd[cmd_index]->out, STDOUT_FILENO);
	close(shell->cmd[cmd_index]->out);
	free(name);
	redirection_arg(shell, cmd_index);
}

void	redirection_input(t_shell *shell, char **args, int cmd_index)
{
	char	*name;
	char	*temp;
	char	cwd[PATH_MAX];

	name = NULL;
	isrediorpipe(shell, args, '<');
	name = getname(args, shell->i, shell->j);
	temp = ft_strjoin(getcwd(cwd, sizeof(cwd)), name);
	free(name);
	name = temp;
	shell->cmd[cmd_index]->in = open(name, O_RDONLY);
	dup2(shell->cmd[cmd_index]->in, STDIN_FILENO);
	close(shell->cmd[cmd_index]->in);
	free(name);
	redirection_arg(shell, cmd_index);
}

