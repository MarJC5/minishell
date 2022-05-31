/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 07:15:38 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/03 19:43:36 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ctrl_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_stat = 128 + SIGINT;
		//rl_replace_line("", 0);
		ft_putendl_fd("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		g_exit_stat = 128 + SIGQUIT;
		rl_on_new_line();
		rl_redisplay();
	}
}
