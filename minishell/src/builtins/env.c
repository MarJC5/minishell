/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:42:05 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/17 11:24:15 by jmartin          ###   ########.fr       */
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
	if (shell->cmd->args_count > 1)
	{
		str_err("env: ", NULL);
		perror(shell->cmd->args[1]);
	}
	else
	{
		while (shell->envp[++i])
		{
			ft_printf("%s", shell->envp[i]);
			if (shell->envp[i + 1] != NULL)
				ft_printf("\n");
		}
	}
}
