/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:54:09 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/14 17:44:13 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	pars_echo_endl(t_shell *shell, char **args, int cmd_index, int start)
{
	size_t	j;
	size_t	i;
	int		find;
	
	i = 0;
	j = 0;
	find = 0;
	while (args[start][i])
	{
		if ((args[start][i] == '-' && args[start][i + 1] == 'n')
			|| (args[start][i] == 'n' && args[start][i + 1] == 'n'))
			find++;
		i++;
	}
    if (start == 0 && args[start][i] == '\0')
    {
        ft_printf("--> %d\n", i - (ft_strlen(shell->cmd[cmd_index]->name) + find + 1));
        shell->cmd[cmd_index]->start = 1;
        shell->bcklash_n = 1;
    }
	else if (args[start][find + 1] == '\0')
	{
        ft_printf("--> %d\n", i - ft_strlen(shell->cmd[cmd_index]->name));
		shell->cmd[cmd_index]->start = 2;
		shell->bcklash_n = 1;
	}
}