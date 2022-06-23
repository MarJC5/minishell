/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:05:05 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/16 13:02:34 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	env_name_size(char *str)
{
	int	i;

	i = 0;
	if (ft_strchr(str, '='))
		i = ft_strlen(str) - ft_strlen(ft_strchr(str, '='));
	else
		i = ft_strlen(str);
	return (i);
}

static int	found_env(t_shell *shell, int env_size, char *value)
{
	int	i;
	int	pos;

	i = -1;
	pos = 0;
	while (shell->envp[++i])
	{
		if (ft_strncmp(shell->envp[i], value, env_size) == 0
			&& env_name_size(shell->envp[i]) == env_size)
			pos = i;
	}
	return (pos);
}

void	*remove_envp(t_shell *shell, char *value, int size)
{
	int		i;
	char	**ret;

	i = -1;
	ret = malloc((size) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (++i < (size - 1))
	{
		if (i < found_env(shell, env_name_size(value), value))
			ret[i] = ft_strdup(shell->envp[i]);
		else if (shell->envp[i + 1] != NULL)
			ret[i] = ft_strdup(shell->envp[i + 1]);
		ft_free_tab(shell->envp[i]);
	}
	ft_free_tab(shell->envp[i]);
	ret[i] = NULL;
	shell->envp = ret;
	return (ret);
}

void	unset(t_shell *shell, int cmd_index)
{
	int	i;

	i = 0;
	g_exit_stat = 1;
	if (shell->cmd[cmd_index]->args_count > 1)
	{
		while (shell->cmd[cmd_index]->args[++i])
		{
			if (shell->cmd[cmd_index]->quotted == 1)
				pars_first_trim(shell, shell->cmd[cmd_index]->args[i], cmd_index, i - 1);
			remove_envp(shell, shell->cmd[cmd_index]->args[i],
				args_counter(shell->envp));
			g_exit_stat = 0;
		}
	}
	else
		str_err("unset: not enough arguments", NULL);
}
