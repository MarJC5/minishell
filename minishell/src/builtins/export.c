/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:27:21 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/15 02:30:49 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Realloc env object and add new item
 *
 * @param shell
 * @param size
 * @param value
 * @return void*
 */

void	*add_envp(t_shell *shell, int size, char *value)
{
	int		i;
	char	**ret;

	i = -1;
	ret = malloc((size + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (++i < (size - 1))
		ret[i] = ft_strdup(shell->envp[i]);
	ret[size - 1] = value;
	ft_free_multi_tab(shell->envp);
	shell->envp = ret;
	return (ret);
}

void	export(t_shell *shell)
{
	int		i;

	i = -1;
	if (shell->cmd->args_count == 1)
		env(shell);
	else if (shell->cmd->args_count > 1)
	{
		update_envp(shell, shell->cmd->args[0], args_counter(shell->envp),
			is_env_valid(shell->cmd->args[0]));
		env(shell);
	}
}
