/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:05:05 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/17 15:33:28 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Realloc env object and remove specified item
 *
 * @param shell
 * @param value
 * @param size
 * @return void*
 */

static int	found_env(t_shell *shell, int env_size, char *value)
{
	int	i;
	int	pos;

	i = -1;
	while (shell->envp[++i])
		if (ft_strncmp(shell->envp[i], value, env_size) == 0)
			pos = i;
	return (pos);
}

void	*remove_envp(t_shell *shell, char *value, int size)
{
	int		i;
	char	**ret;
	int		env_name_size;

	i = -1;
	env_name_size = is_env_valid(value);
	ret = malloc((size) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (++i < (size - 1))
	{
		if (i < found_env(shell, env_name_size, value))
			ret[i] = ft_strdup(shell->envp[i]);
		else
			ret[i] = ft_strdup(shell->envp[i + 1]);
		ft_free_tab(shell->envp[i]);
	}
	ret[i] = NULL;
	shell->envp = ret;
	return (ret);
}

void	unset(t_shell *shell)
{
	if (shell->cmd->args_count > 1)
		remove_envp(shell, shell->cmd->args[1], args_counter(shell->envp) - 1);
	else
		str_err("unset: not enough arguments", NULL);
}
