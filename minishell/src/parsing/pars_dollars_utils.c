/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_dollars_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:52:51 by jmartin           #+#    #+#             */
/*   Updated: 2022/07/01 10:44:34 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	empty_dollar(t_shell *shell, int cmd_index, int i, char *dols)
{
	char	*tmp;

	tmp = ft_replace_empty(shell->cmd[cmd_index]->args[i], dols - 1, 0);
	ft_free_tab(shell->cmd[cmd_index]->args[i]);
	shell->cmd[cmd_index]->args[i] = tmp;
}

void	env_name(t_shell *shell, int j)
{
	shell->env_name = ft_strchr_env(shell->envp[j], '=');
	shell->env_size = ft_strlen(shell->env_name);
}
