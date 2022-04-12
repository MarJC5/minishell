/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:47:44 by jmartin           #+#    #+#             */
/*   Updated: 2022/04/11 14:52:21 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_cd(t_shell *shell, int cmd_index)
{
<<<<<<< HEAD
	int	i;
=======
	int		i;
>>>>>>> main

	i = 0;
	while (shell->cmd[cmd_index]->args[i])
	{
		if (shell->cmd[cmd_index]->args[i][0] == 'c'
			&& shell->cmd[cmd_index]->args[i][1] == 'd'
			&& shell->cmd[cmd_index]->args[i][2] == '\0')
			break ;
		i++;
	}
	i++;
	if (chdir(shell->cmd[cmd_index]->args[i]) == -1)
	{
		ft_printf("cd: ");
		perror(shell->cmd[cmd_index]->args[i]);
	}
	else
<<<<<<< HEAD
		chdir(shell->cmd[cmd_index]->args[i]);
=======
		chdir(shell->cmd->args[i]);
>>>>>>> main
	ft_printf("%s", getcwd(shell->current_path, 100));
}
