/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:13:55 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/20 16:38:52 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*pars_cr_realloc(char *args, char *newval, int i, int j)
{
	char	*begin;
	char	*end;
	char	*tmp;

	begin = NULL;
	end = NULL;
	tmp = NULL;
	ft_printf("|> %s\n", args);
	if (args[i] == '$')
	{
		ft_printf("|-> %s\n", args);
		begin = ft_substr(args, 0, i);
		end = ft_substr(args, j, (int)ft_strlen(args) - j);
		tmp = ft_strjoin(begin, newval);
		args = ft_strjoin(tmp, end);
		ft_printf("|--> %s\n", args);
		free(begin);
		free(end);
		free(tmp);
	}
	return (args);
}

char	*pars_cr_arg(t_shell *shell, char *args, int j)
{
	char	*str;

	if (args[j] == '$')
	{
		if (args[j + 1] == '?')
			return (pars_cr_realloc(args, ft_itoa(g_exit_stat), j, 2));
		else if (args[j + 1] != '\0')
		{
			str = get_env_var(shell, args);
			if (str != NULL)
				return (pars_cr_realloc(args, str, j, ft_strlen(str) + 2));
			else
				return (args);
		}
	}
	return (NULL);
}

void	pars_remove_quote(t_shell *shell, int cmd_index, int c, int out)
{
	int	i;
	int	j;
	int	spose;
	int	dpose;

	i = 0;
	while (shell->cmd[cmd_index]->args[i])
	{
		spose = ft_strchr_pos(shell->cmd[cmd_index]->args[i], c);
		dpose = ft_strchr_pos(shell->cmd[cmd_index]->args[i], out);
		if (dpose >= 0)
		{
			if (spose >= 0)
			{
				j = spose;
				while (shell->cmd[cmd_index]->args[i][j])
				{
					j++;
					if (shell->cmd[cmd_index]->args[i][j] == c)
						break ;
				}
				if (spose < dpose && j > dpose)
					;
			}
			else
				remove_char(shell->cmd[cmd_index]->args[i], out);
		}
		i++;
	}
}
