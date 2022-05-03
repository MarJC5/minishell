/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:26:54 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/03 19:27:03 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ascii_prompt(void)
{
	ft_printf("\n\033[1;32m░█▀▄▀█░░▀░░█▀▀▄░░▀░░█▀▀░█░░░░█▀▀░█░░█░\n");
	ft_printf("░█░▀░█░░█▀░█░▒█░░█▀░▀▀▄░█▀▀█░█▀▀░█░░█░\n");
	ft_printf("░▀░░▒▀░▀▀▀░▀░░▀░▀▀▀░▀▀▀░▀░░▀░▀▀▀░▀▀░▀▀\n");
	ft_printf("\033[0;32mby Tpaquier & Jmartin                   \033[0m\n\n");
}
