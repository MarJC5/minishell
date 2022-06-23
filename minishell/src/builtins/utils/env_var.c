/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:52:16 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/16 11:25:57 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	*get_env_var(t_shell *shell, char *arg)
{
	int		i;
	int		var_len;
	char	*var;
	char	*str;

	i = -1;
	str = NULL;
	while (shell->envp[++i] != NULL)
	{
		var_len = ft_strchr_pos(shell->envp[i], '=');
		if (var_len > 0)
		{
			var = ft_substr(shell->envp[i], 0, var_len);
			shell->env_size = var_len - 1;
			if (ft_strcmp(var, ft_strrchr(arg, '$') + 1) == 0)
			{
				str = ft_strtrim(shell->envp[i] + var_len, "=");
				free(var);
				break;
			}
			free(var);
		}
	}
	return (str);
}

char	*env_updater(t_shell *shell, char *name, char *value)
{
	int		i;
	char	*old;

	i = -1;
	while (++i < args_counter(shell->envp))
	{
		shell->env_size = ft_strchr_pos(shell->envp[i], '=');
		if (shell->env_size > 0)
		{
			old = ft_substr(shell->envp[i], 0, shell->env_size + 1);
			if (ft_strncmp(name, old, shell->env_size - 1) == 0)
			{
				free(shell->envp[i]);
				shell->envp[i] = ft_strjoin(old, value);
				free(old);
				return (shell->envp[i]);
			}
			free(old);
		}
	}
	return (NULL);
}