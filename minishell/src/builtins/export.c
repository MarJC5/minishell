/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:27:21 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/20 16:34:34 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	swap_env(char **env)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	temp = NULL;
	while (i < args_counter(env))
	{
		j = 0;
		while (j < args_counter(env) - 1 - i)
		{
			if (env[j] && ft_strcmp(env[j], env[j + 1]) > 0)
			{
				temp = ft_strdup(env[j]);
				ft_free_tab(env[j]);
				env[j] = ft_strdup(env[j + 1]);
				ft_free_tab(env[j + 1]);
				env[j + 1] = ft_strdup(temp);
				ft_free_tab(temp);
			}
			j++;
		}
		i++;
	}
}

static void	sort_export(t_shell *shell)
{
	char	**env_dup;
	int		size;
	int		i;

	i = -1;
	size = args_counter(shell->envp);
	env_dup = malloc((size + 1) * sizeof(char *));
	if (!env_dup)
		return ;
	while (++i < size)
		env_dup[i] = ft_strdup(shell->envp[i]);
	env_dup[i] = NULL;
	swap_env(env_dup);
	i = -1;
	while (++i < size)
		ft_printf("%s\n", env_dup[i]);
	ft_free_multi_tab(env_dup);
}

void	*add_envp(t_shell *shell, int size, char *value)
{
	int		i;
	char	**ret;

	i = -1;
	ret = malloc((size + 2) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (++i < (size - 1))
	{
		ret[i] = ft_strdup(shell->envp[i]);
		ft_free_tab(shell->envp[i]);
	}
	ret[i++] = value;
	ret[i] = NULL;
	shell->envp = ret;
	return (ret);
}

void	export(t_shell *shell, int cmd_index)
{
	int	i;

	i = 0;
	g_exit_stat = 1;
	if (shell->cmd[cmd_index]->args_count == 1)
		sort_export(shell);
	else if (shell->cmd[cmd_index]->args_count > 1)
	{
		if (shell->cmd[cmd_index]->args[1][0] == '=')
			str_err("export: not valid in this context: ",
				shell->cmd[cmd_index]->args[1]);
		else
		{
			while (shell->cmd[cmd_index]->args[++i])
			{
				update_envp(shell, shell->cmd[cmd_index]->args[i],
					args_counter(shell->envp),
					is_env_valid(shell->cmd[cmd_index]->args[i]));
				g_exit_stat = 0;
			}
		}
	}
}
