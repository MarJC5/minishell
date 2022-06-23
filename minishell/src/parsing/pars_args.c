/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 08:46:53 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/16 12:52:52 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pars_cmd_name_quote(char *str)
{
	if (quote_counter(str, '\"') == 0)
		remove_char(str, '\"');
	if (quote_counter(str, '\'') == 0)
		remove_char(str, '\'');
}

char	**pars_join(t_shell *shell, char *args, char c, int cmd_index)
{
	int		i;
	char	**tmp;
	char	*merge;
	char	*new_args;

	i = 0;
	shell->cmd[cmd_index]->quotted = 1;
	tmp = ft_split(args, c);
	merge = ft_strdup("");
	while (tmp[i])
	{
		new_args = ft_strjoin(merge, append('\"', tmp[i], '\"'));
		free(merge);
		merge = ft_strdup(new_args);
		free(new_args);
		i++;
	}
	shell->cmd[cmd_index]->pars_args = ft_strdup(merge);
	ft_printf("|-> %s\n-----------\n", shell->cmd[cmd_index]->pars_args);
	free(merge);
	return (tmp);
}

void	pars_args(t_shell *shell, char *args, int cmd_index)
{
	char	**tmp;

	tmp = ft_split(args, ' ');
	shell->cmd[cmd_index] = malloc(sizeof(t_cmd));
	shell->cmd[cmd_index]->shell = shell;
	shell->cmd[cmd_index]->in = -1;
	shell->cmd[cmd_index]->out = -1;
	shell->cmd[cmd_index]->pid = -1;
	shell->cmd[cmd_index]->cmd_pos = cmd_index;
	shell->cmd[cmd_index]->quotted = 0;
	shell->cmd[cmd_index]->name = ft_strdup(tmp[0]);
	pars_cmd_name_quote(shell->cmd[cmd_index]->name);
	shell->cmd[cmd_index]->pars_args = NULL;
	if (ft_strchr(args, '\"') != NULL)
		shell->cmd[cmd_index]->args = pars_join(shell, args, '\"', cmd_index);
	else
		shell->cmd[cmd_index]->args = ft_split(args, ' ');
	shell->cmd[cmd_index]->args_count = args_counter(
			shell->cmd[cmd_index]->args);
	shell->cmd_count++;
	ft_free_multi_tab(tmp);
}

