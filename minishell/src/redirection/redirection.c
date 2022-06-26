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

// >> test XXX pour les redis : change bien le cmd->name mais dans init_func tjr l'ancien
// rajoute les heredocs alors que ca devrais les supprimer --
// lance la redis même si la commande n'existe pas : pas besoin de changer

void	ft_cmd_name_changer(t_shell *shell, int cmd_index)
{
	ft_free_tab(shell->cmd[cmd_index]->name);
	shell->cmd[cmd_index]->name = NULL;
	shell->cmd[cmd_index]->name = ft_strdup(shell->cmd[cmd_index]->args[0]);
}

void	redirection(t_shell *shell, int cmd_index)
{
	char	*name;
	char	*temp;
	char	cwd[PATH_MAX];

	name = NULL;
	shell->cmd[cmd_index]->namei = 0;
	shell->cmd[cmd_index]->namej = 0;
	isrediorpipe(shell, cmd_index, '>');
	name = getname(shell, shell->cmd[cmd_index]->args, shell->i, shell->j, cmd_index);
	temp = ft_strjoin(getcwd(cwd, sizeof(cwd)), name);
	free(name);
	name = temp;
	if (isdoubleredi(shell->cmd[cmd_index]->args, '>') == 2)
		shell->cmd[cmd_index]->out = open(name, O_CREAT | O_RDWR | O_APPEND, 0666);
	else
		shell->cmd[cmd_index]->out = open(name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	dup2(shell->cmd[cmd_index]->out, STDOUT_FILENO);
	close(shell->cmd[cmd_index]->out);
	shell->cmd[cmd_index]->args = redirection_arg(shell, cmd_index,
		shell->cmd[cmd_index]->namei, shell->cmd[cmd_index]->namej);
	free(name);
	if (isrediorpipe(shell, cmd_index, '>') == 1)
		redirection(shell, cmd_index);
	ft_cmd_name_changer(shell, cmd_index);
}
