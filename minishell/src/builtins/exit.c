/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:52:30 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/16 12:14:16 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit(t_shell *shell, int cmd_index)
{
	(void) cmd_index;
	ft_free_read_args(shell, NULL);
	free(shell);
	exit(g_exit_stat);
}
