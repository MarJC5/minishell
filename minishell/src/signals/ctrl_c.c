/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 07:15:38 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/17 16:31:30 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ctrl_c_handler(int sig)
{
	if (sig)
	{
		rl_replace_line("", 0);
		ft_putendl_fd("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}
