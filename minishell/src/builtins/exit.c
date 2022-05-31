/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:52:30 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/31 07:32:31 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit(t_shell *shell, int cmd_index)
{
	if (shell->cmd[cmd_index]->args_count > 1)
	{
		g_exit_stat = 1;
		str_err("exit: too many arguments", NULL);
	}
	else
	{
		g_exit_stat = 0;
		ft_free_read_args(shell, NULL);
		free(shell);
		exit(EXIT_SUCCESS);
	}
}
