/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:05:05 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/14 17:47:25 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	remove_envp(t_shell *shell, char *value, int size)
{
	int	i;
	int	pos;
	int	env_name_size;

	i = -1;
	env_name_size = is_env_valid(value);
	while (shell->envp[++i])
	{
		if (ft_strncmp(shell->envp[i], value, env_name_size) == 0)
			shell->envp[i] = NULL;
	}
	i = -1;
	while (shell->envp[++i])
	{
		if (shell->envp[i + 1] != NULL)
		{
			free(shell->envp[i]);
			shell->envp[i] = ft_strdup(shell->envp[i + 1]);
		}
	}
	shell->envp[size - 1] = NULL;
}

void	unset(t_shell *shell)
{
	remove_envp(shell, shell->cmd.args[0], args_counter(shell->envp));
	env(shell);
}
