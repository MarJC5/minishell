/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:05:05 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/15 02:08:02 by jmartin          ###   ########.fr       */
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

void	*remove_envp(t_shell *shell, char *value, int size)
{
	int		i;
	int		pos;
	char	**ret;
	int		env_name_size;

	i = -1;
	env_name_size = is_env_valid(value);
	ret = malloc((size + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (shell->envp[++i])
		if (ft_strncmp(shell->envp[i], value, env_name_size) == 0)
			pos = i;
	i = -1;
	while (++i < (size - 1))
	{
		if (i < pos)
			ret[i] = ft_strdup(shell->envp[i]);
		else
			ret[i] = ft_strdup(shell->envp[i + 1]);
	}
	ft_free_multi_tab(shell->envp);
	shell->envp = ret;
	return (ret);
}

void	unset(t_shell *shell)
{
	if (ft_strlen(shell->cmd.args[0]))
		remove_envp(shell, shell->cmd.args[0], args_counter(shell->envp));
	env(shell);
}
