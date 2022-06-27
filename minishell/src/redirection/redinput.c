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

int	ft_err_redinput(char *name)
{
	str_err("minishell: file not found: ", name);
	free(name);
	return (1);
}

char	*redinput_name(t_shell *shell, int cmd_index)
{
	char	cwd[PATH_MAX];
	char	*name;
	char	*temp;

	temp = NULL;
	name = NULL;
	name = getname(shell, shell->i, shell->j, cmd_index);
	temp = ft_strjoin(getcwd(cwd, sizeof(cwd)), name);
	free(name);
	name = temp;
	return (name);
}

int	redirection_input(t_shell *shell, int cmd_index)
{
	char	*name;
	int		i;

	name = NULL;
	i = 0;
	shell->cmd[cmd_index]->namei = 0;
	shell->cmd[cmd_index]->namej = 0;
	isrediorpipe(shell, cmd_index, '<');
	name = redinput_name(shell, cmd_index);
	shell->cmd[cmd_index]->in = open(name, O_RDONLY);
	dup2(shell->cmd[cmd_index]->in, STDIN_FILENO);
	if (shell->cmd[cmd_index]->in != -1)
		close(shell->cmd[cmd_index]->in);
	shell->cmd[cmd_index]->args = redirection_arg(shell, cmd_index,
			shell->cmd[cmd_index]->namei, shell->cmd[cmd_index]->namej);
	if (shell->cmd[cmd_index]->in == -1)
		return (ft_err_redinput(name));
	free(name);
	//ft_cmd_name_changer(shell, cmd_index);
	if (isrediorpipe(shell, cmd_index, '<') == 1)
		return (redirection_input(shell, cmd_index));
	while (i++ < 10000000)
		;
	return (0);
}
