/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:52:30 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/03 15:02:39 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit(t_shell *shell, int cmd_index)
{
	(void) cmd_index;
	g_exit_stat = 0;
	ft_free_read_args(shell, NULL);
	free(shell);
	exit(0);
}
