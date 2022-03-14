/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:27:21 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/14 19:13:30 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*format_envp(char *value, int size, int is_new)
{
	char	*var;
	char	*arg;
	char	*ret;

	if (ft_strchr(value, ' '))
	{
		arg = ft_substr(value, size + 1, ft_strlen(value));
		var = ft_substr(value, 0, size + 1);
		ret = ft_strjoin(var, append('\'', arg, '\''));
		free(arg);
		free(var);
	}
	else if (is_new && ft_strchr(value, '=') == NULL)
		ret = ft_strjoin(value, "=\'\'");
	else
		ret = ft_strdup(value);
	return (ret);
}

static void	update_envp(t_shell *shell, char *value, int size, int is_valid)
{
	int	i;

	i = -1;
	if (is_valid)
	{
		while (shell->envp[++i])
		{
			if (ft_strncmp(shell->envp[i], value, is_valid) == 0
				&& ft_strchr(value, '=') == NULL)
				break ;
			if (ft_strncmp(shell->envp[i], value, is_valid) == 0
				&& ft_strcmp(shell->envp[i], value) != 0)
			{
				free(shell->envp[i]);
				shell->envp[i] = format_envp(value, is_valid, 0);
				break ;
			}
			else if (ft_strncmp(shell->envp[i], value, is_valid) != 0
				&& i == size - 1)
			{
				ft_realloc_env(shell, args_counter(shell->envp) + 1,
					format_envp(value, is_valid, 1));
			}
		}
	}
}

/**
 * @brief Set/overwrite the export object
 *
 * @param shell
 */

void	export(t_shell *shell)
{
	int		i;

	i = -1;
	if (shell->cmd.args_count == 1)
		env(shell);
	else if (shell->cmd.args_count > 1)
	{
		update_envp(shell, shell->cmd.args[0], args_counter(shell->envp),
			is_env_valid(shell->cmd.args[0]));
		env(shell);
	}
}
