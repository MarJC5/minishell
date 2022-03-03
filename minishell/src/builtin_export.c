/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:27:21 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/03 09:10:34 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Get the export env object
 *
 * @param envp
 */

static void	get_export_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		ft_printf("%s\n", envp[i++]);
}

/**
 * @brief Set/overwrite the export object
 *
 * @param command
 * @param envp
 */

void	set_export(t_cmd *command, char **envp)
{
	if (command->args_count == 1)
		get_export_env(envp);
	else if (command->args_count > 1)
		ft_printf("%s", command->args[0]);
}
