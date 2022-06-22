/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:54:09 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/20 16:37:29 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	pars_first_trim(t_shell *shell, char *args, int cmd_index, int i)
{
	size_t	trim;
	size_t	start;
	char	*tmp;
	char	*tmp2;

	if (args)
	{
		start = ft_strlen(shell->cmd[cmd_index]->name) + 1;
		trim = ft_strlen(shell->cmd[cmd_index]->args[i]);
		if (shell->bcklash_n == 1)
			start += 3;
		if (trim > 0)
		{
			tmp = ft_substr(shell->cmd[cmd_index]->args[i], start, trim);
			tmp2 = ft_strdup(args);
			free(shell->cmd[cmd_index]->args[i + 1]);
			shell->cmd[cmd_index]->args[i + 1] = ft_strjoin(
					ft_strtrim(tmp, "\""), ft_strtrim(tmp2, "\""));
			free(tmp);
			free(tmp2);
		}
	}
}

void	pars_echo_endl(t_shell *shell, char **args, int cmd_index, int start)
{
	size_t	i;
	int		find;

	i = -1;
	find = 0;
	while (args[start] && args[start][++i])
	{
		if ((args[start][i] == '-' && args[start][i + 1] == 'n')
			|| (args[start][i] == 'n' && args[start][i + 1] == 'n'))
			find++;
	}
	if (start == 0 && args[start][i] == '\0')
	{
		shell->cmd[cmd_index]->start = 1;
		shell->bcklash_n = 1;
	}
	else if (args[start] && args[start][find + 1] == '\0')
	{
		shell->cmd[cmd_index]->start = 2;
		shell->bcklash_n = 1;
	}
	if (shell->bcklash_n == 1)
		pars_first_trim(shell, args[start + 1], cmd_index, start);
	else
		pars_first_trim(shell, args[start], cmd_index, start - 1);
}
