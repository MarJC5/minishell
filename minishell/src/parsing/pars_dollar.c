/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:52:51 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/28 20:19:00 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


static void	empty_dollar(t_shell *shell, int cmd_index, int i, char *dols)
{
	char	*tmp;

	tmp = ft_replace_empty(shell->cmd[cmd_index]->args[i], dols - 1, 0);
	ft_free_tab(shell->cmd[cmd_index]->args[i]);
	shell->cmd[cmd_index]->args[i] = tmp;
}
/*
static void	swap_doll(t_shell *shell, int cmd_index, int i, char *tmp)
{
	ft_free_tab(shell->cmd[cmd_index]->args[i]);
	shell->cmd[cmd_index]->args[i] = tmp;
}
*/
void	pars_dollars(t_shell *shell, int cmd_index, int i, char *tmp)
{
	int		j;
	char	*dols;
	char	*env_name;
	size_t	env_size;

	j = 0;
	dols = ft_strchr_no_delimiter(shell->cmd[cmd_index]->args[i], '$');
	if (dols == NULL)
		return ;
	while (shell->envp[j])
	{
		env_name = ft_strchr_env(shell->envp[j], '=');
		env_size = ft_strlen(env_name);
		if (dols[0] == '?')
		{
			tmp = ft_replace_inter(g_exit_stat,
					shell->cmd[cmd_index]->args[i], NULL, 0);
			if (tmp != NULL)
			{
				ft_free_tab(shell->cmd[cmd_index]->args[i]);
				shell->cmd[cmd_index]->args[i] = tmp;
			}
			break ;
		}
		if (ft_strncmp(dols, env_name, env_size) == 0)
		{
			tmp = ft_replace_dols(ft_strchr(shell->envp[j], '=') + 1,
					shell->cmd[cmd_index]->args[i], env_size, dols - 1);
			if (tmp != NULL)
			{
				ft_free_tab(shell->cmd[cmd_index]->args[i]);
				shell->cmd[cmd_index]->args[i] = tmp;
			}
			break ;
		}
		j++;
		if (!shell->envp[j])
			empty_dollar(shell, cmd_index, i, dols);
		free(env_name);
	}
	dols = ft_strchr_no_delimiter(shell->cmd[cmd_index]->args[i], '$');
	if (dols && tmp != NULL)
		pars_dollars(shell, cmd_index, i, NULL);
}
