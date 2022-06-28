/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 07:15:38 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/12 21:00:58 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ctrl_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_exit_stat == -1)
		{
			g_exit_stat = 128 + SIGINT;
			return ;
		}
		rl_replace_line("", 0);
		ft_putendl_fd("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_stat = 1;
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		g_exit_stat = 128 + SIGQUIT;
	}
}
