/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:27:21 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/08 16:42:57 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <string.h>

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

void	sort_export(t_shell *shell)
{
	char	*temp;
	char	**env_dup;
	int		i;

	i = -1;
	temp = NULL;
	env_dup = malloc((args_counter(shell->envp)) * sizeof(char *));
	while (++i < args_counter(shell->envp))
		env_dup[i] = format_envp(shell->envp[i], 
			is_env_valid(shell->envp[i]), 0);
	for (int i = 0; i < args_counter(env_dup); i++)
	{
		for (int j = 0; j < args_counter(env_dup) - 1 - i; j++)
		{
			if (strcmp(env_dup[j], env_dup[j + 1]) > 0)
			{
				strcpy(temp, env_dup[j]);
				strcpy(env_dup[j], env_dup[j + 1]);
				strcpy(env_dup[j + 1], temp);
			}
		}
	}
	i = -1;
	while (++i < args_counter(env_dup))
		ft_printf("%s\n", env_dup[i]);
	ft_free_multi_tab(env_dup);
}

void	export(t_shell *shell, int cmd_index)
{
	int	i;

	i = 0;
	g_exit_stat = 0;
	if (shell->cmd[cmd_index]->args_count == 1)
		sort_export(shell);
	else if (shell->cmd[cmd_index]->args_count > 1)
	{
		if (shell->cmd[cmd_index]->args[1][0] == '=')
		{
			g_exit_stat = 1;
			str_err("export: not valid in this context: ",
				shell->cmd[cmd_index]->args[1]);
		}
		else
		{
			while (shell->cmd[cmd_index]->args[++i])
			{
				update_envp(shell, shell->cmd[cmd_index]->args[i],
					args_counter(shell->envp),
					is_env_valid(shell->cmd[cmd_index]->args[i]));
			}
		}
	}
}
