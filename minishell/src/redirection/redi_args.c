/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:45:11 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/31 10:05:32 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cna(t_shell *shell, int endi, int endj, int cmd_index)
{
	int	i;
	int	ct;

	i = 0;
	ct = 0;
	while (shell->cmd[cmd_index]->args[i])
	{
		if (i == shell->i && shell->j == 0)
		{
			i = endi;
			if ((size_t)endj != ft_strlen(shell->cmd[cmd_index]->args[i]))
				ct++;
		}
		else if (i == shell->i && shell->j != 0)
		{
			i = endi;
			ct++;
		}
		else
			ct++;
		i++;
	}
	ct++;
	return (ct);
}

void	ft_free_tmp(char **tmp)
{
	int	g;

	g = (args_counter(tmp));
	while (g >= 0)
		ft_free_tab(tmp[g--]);
	free(tmp);
	tmp = NULL;
}

void	ft_free_args(t_shell *shell, int cmd_index, int count)
{
	while (count >= 0)
		ft_free_tab(shell->cmd[cmd_index]->args[count--]);
	free(shell->cmd[cmd_index]->args);
	shell->cmd[cmd_index]->args = NULL;
}

void	ft_seteur_var(int *count, int *i2)
{
	*count = 0;
	*i2 = 0;
}

char	**redirection_arg(t_shell *shell, int cmd_index, int i, int j)
{
	char	**str;
	char	**tmp;
	int		count;
	int		i2;

	ft_seteur_var(&count, &i2);
	str = ft_calloc(ft_cna(shell, i, j, cmd_index), sizeof(char *));
	while (shell->cmd[cmd_index]->args[count])
	{
		if (count != shell->i)
			str[i2++] = ft_strdup(shell->cmd[cmd_index]->args[count++]);
		else
		{
			tmp = ft_split_with_delimiter(shell->cmd[cmd_index]->args[count],
					shell->cmd[cmd_index]->args[shell->i][shell->j]);
			if (shell->j != 0)
				str[i2++] = ft_strdup(tmp[0]);
			if (shell->cmd[cmd_index]->args[i][j])
				str[i2++] = ft_strdup(&shell->cmd[cmd_index]->args[i][j]);
			count = i + 1;
			ft_free_tmp(tmp);
		}
	}
	ft_free_args(shell, cmd_index, count);
	return (str);
}
