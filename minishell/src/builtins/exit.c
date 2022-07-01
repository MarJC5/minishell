/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:52:30 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/16 12:14:16 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_exit_val(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (!ft_isdigit(value[i]))
			return (str_err("minishell: numeric argument required: ",
					value));
		i++;
	}
	return (ft_atoi(value));
}

static void	ft_exit_check(t_shell *shell, int cmd_index)
{
	if (shell->cmd[cmd_index]->args[1])
		g_exit_stat = ft_exit_val(shell->cmd[cmd_index]->args[1]);
}

void	ft_exit(t_shell *shell, int cmd_index)
{
	if (shell->ispipe == 0)
		ft_printf("exit\n");
	ft_exit_check(shell, cmd_index);
	ft_free_tab(shell->line);
	ft_free_multi_tab(shell->envp);
	ft_free_tab(shell->current_path);
	ft_free_read_args(shell, NULL);
	free(shell);
	exit(g_exit_stat);
}
