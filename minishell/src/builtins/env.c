/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:42:05 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/16 14:07:26 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Print all env
 *
 * @param shell
 */

void	env(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->envp[++i])
	{
		ft_printf("%s", shell->envp[i]);
		if (shell->envp[i + 1] != NULL)
			ft_printf("\n");
	}
}
