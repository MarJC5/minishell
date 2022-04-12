/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:47:54 by jmartin           #+#    #+#             */
/*   Updated: 2022/04/11 19:35:17 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	isp(char **str, int i, int ret)
{
	int	j;

	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '|' || str[i][j] == '>')
			{
				if (ret == 1)
					return (j);
				if (ret == 0)
					return (i);
			}
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * @brief
 * start = premier arguments après echo
 * count = nombre d'argument entre la premiere lettre de i et le pipe
*/

void	ft_pipe(t_shell *shell, char **args, int i)
{
	(void) i;
	if (isrediorpipe(shell, args, '>') == 1)
		redirection(shell, args);
}

void	ft_wbn(t_shell *shell, char **args, int i)
{
	shell->bcklash_n = 1;
	if (isp(args, i, 0) == 0)
	{
		while (args[i])
		{
			ft_printf("%s", args[i++]);
			if (args[i])
				ft_printf(" ");
		}
		ft_printf("\n");
	}
	else
		ft_pipe(shell, args, i);
}

void	ft_nbn(t_shell *shell, char **args, int i)
{
	if (isp(args, i, 0) == 0)
	{
		while (args[i])
		{
			ft_printf("%s", args[i++]);
			if (args[i] != NULL)
				ft_printf(" ");
		}
	}
	else
		ft_pipe(shell, args, i);
}

void	ft_echo(t_shell *shell, int cmd_index)
{
	shell->bcklash_n = 0;
	if (shell->cmd[cmd_index]->args[1])
	{
		if (shell->cmd[cmd_index]->args[1][0] == '-'
			&& shell->cmd[cmd_index]->args[1][1] == 'n')
			ft_nbn(shell, shell->cmd[cmd_index]->args, 2);
		else
			ft_wbn(shell, shell->cmd[cmd_index]->args, 1);
	}
	else
		ft_printf("\n");
}
