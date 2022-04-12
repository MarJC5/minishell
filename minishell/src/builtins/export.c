/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:27:21 by jmartin           #+#    #+#             */
/*   Updated: 2022/04/11 15:06:31 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	if (shell->cmd[cmd_index]->args_count == 1)
		env(shell, 0);
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
			}
		}
	}
}
