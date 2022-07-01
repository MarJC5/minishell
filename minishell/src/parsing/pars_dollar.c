/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:52:51 by jmartin           #+#    #+#             */
/*   Updated: 2022/07/01 11:00:33 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	replace_dolss(t_shell *shell, int cmd_index, int i, char *tmp)
{
	ft_free_tab(shell->cmd[cmd_index]->args[i]);
	shell->cmd[cmd_index]->args[i] = tmp;
}

static int	ft_set_value_dolls(t_shell *shell, int cmd_index, int i)
{
	shell->ct_dols = 0;
	shell->dols = NULL;
	shell->dols = ft_strchr_no_delimiter(shell->cmd[cmd_index]->args[i], '$');
	if (shell->dols == NULL)
		return (1);
	return (0);
}

static char	*ret_norm(t_shell *shell, int cmd_index, int i)
{
	char	*ret;

	ret = ft_replace_dols(ft_strchr(shell->envp[shell->ct_dols], '=') + 1,
			shell->cmd[cmd_index]->args[i], shell->env_size,
			shell->dols - 1);
	if (shell->env_name)
		free(shell->env_name);
	return (ret);
}

static void	recursif(t_shell *shell, int cmd_index, int i)
{
	shell->ct_dols++;
	if (!shell->envp[shell->ct_dols])
		empty_dollar(shell, cmd_index, i, shell->dols);
	if (shell->env_name)
		free(shell->env_name);
}

void	pars_dollars(t_shell *shell, int cmd_index, int i, char *tmp)
{
	if (ft_set_value_dolls(shell, cmd_index, i) == 1)
		return ;
	while (shell->envp[shell->ct_dols])
	{
		env_name(shell, shell->ct_dols);
		if (shell->dols[0] == '?')
		{
			tmp = ft_replace_inter(g_exit_stat,
					shell->cmd[cmd_index]->args[i], NULL, 0);
			if (tmp != NULL)
				replace_dolss(shell, cmd_index, i, tmp);
			break ;
		}
		if (ft_strncmp(shell->dols, shell->env_name, shell->env_size) == 0)
		{
			tmp = ret_norm(shell, cmd_index, i);
			if (tmp != NULL)
				replace_dolss(shell, cmd_index, i, tmp);
			break ;
		}
		recursif(shell, cmd_index, i);
	}
	shell->dols = ft_strchr_no_delimiter(shell->cmd[cmd_index]->args[i], '$');
	if (shell->dols && tmp != NULL)
		pars_dollars(shell, cmd_index, i, NULL);
}
