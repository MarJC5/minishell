/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:27:21 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/07 08:02:26 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Get the export env object, count his size and print if needed
 */

void	get_export_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		ft_printf("%s\n", envp[i]);
}

/**
 * @brief Set/overwrite the export object
 *
 * @param command
 * @param envp
 */

void	set_export(t_shell *shell)
{
	int	i;

	i = -1;
	ft_printf("ENV size before = %i\n", args_counter(shell->envp));
	if (shell->cmd->args_count == 1)
		get_export_env(shell->envp);
	else if (shell->cmd->args_count > 1)
	{
		ft_realloc_env(shell->envp, args_counter(shell->envp) + 1);
		//shell->envp[args_counter(shell->envp) - 1] = ft_strdup("hello");
		ft_printf("ENV size after = %i\n", args_counter(shell->envp));
	}
}
