/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:42:05 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/15 02:06:48 by jmartin          ###   ########.fr       */
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
		ft_printf("%s\n", shell->envp[i]);
}
