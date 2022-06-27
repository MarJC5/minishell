/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 00:11:56 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/28 00:20:32 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	pars_sp_loop_sq(t_shell *shell, int cmd_index, int *i, int *count)
{
	if (shell->sq == '\0')
		quote_finder(shell, cmd_index, *i);
	else if (shell->sq != '\0')
	{
		quote_finder_two(shell, shell->cmd[cmd_index]->args[*i], 1);
		if (shell->sq != '\0' && shell->eq != '\0')
		{
			*count = 0;
			ft_reset_eq_sq(shell);
		}
		if (shell->sq != '\0' && shell->eq == '\0')
			*count += 1;
	}
}

static void	pars_space_free(t_shell *shell, int cmd_index, int i)
{
	while (i >= 0)
		ft_free_tab(shell->cmd[cmd_index]->args[i--]);
	free(shell->cmd[cmd_index]->args);
}

char	**pars_space(t_shell *shell, int i, int i2, int cmd_index)
{
	char	**tmp;
	int		count;

	count = 0;
	tmp = ft_calloc(ft_counter_space(shell,
				shell->cmd[cmd_index]->args, cmd_index), sizeof(char *));
	ft_reset_eq_sq(shell);
	while (i < args_counter(shell->cmd[cmd_index]->args) - 1)
	{
		pars_sp_loop_sq(shell, cmd_index, &i, &count);
		if (ft_onlyspace(shell->cmd[cmd_index]->args[i]) && count == 0)
			i++;
		else
		{
			if (shell->sq == '\0')
				tmp[i2++] = ft_strdup(shell->cmd[cmd_index]->args[i++]);
			else
				tmp[i2++] = ft_join_quote(shell, cmd_index, &i);
			if (i != args_counter(shell->cmd[cmd_index]->args) - 1)
				quote_finder_two(shell, shell->cmd[cmd_index]->args[i], 0);
		}
	}
	pars_space_free(shell, cmd_index, 0);
	return (pars_remove_quote_out(tmp, 0, '\0'));
}
