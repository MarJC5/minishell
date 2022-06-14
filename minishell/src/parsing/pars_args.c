/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 08:46:53 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/14 17:28:36 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_read_quote(char *str)
{
	if (quote_counter(str, '\"') == 1
		|| quote_counter(str, '\'') == 1)
	{
		g_exit_stat = 127;
		str_err("minishell: syntax error", NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	pars_cmd_name_quote(char *str)
{
	if (quote_counter(str, '\"') == 0)
		remove_char(str, '\"');
	else if (quote_counter(str, '\'') == 0)
		remove_char(str, '\'');
}

char	**pars_join(t_shell *shell, char *args, char c, int cmd_index)
{
	int		i;
	char	**tmp;
	char	*merge;
	char	*new_args;

	i = 0;
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
	i = (int)ft_strlen(merge) - (int)ft_strlen(shell->cmd[cmd_index]->name);
	shell->cmd[cmd_index]->pars_args = ft_substr(merge,
			ft_strlen(shell->cmd[cmd_index]->name) + 1, i);
	free(merge);	
	for (int i = 0; i < args_counter(tmp); i++)
	{
		ft_printf("-> %s\n",tmp[i]);
	}
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
	shell->cmd[cmd_index]->name = arg_to_lower(ft_strdup(tmp[0]));
	pars_cmd_name_quote(shell->cmd[cmd_index]->name);
	shell->cmd[cmd_index]->pars_args = NULL;
	if (ft_strchr(args, '\"') != NULL)
		shell->cmd[cmd_index]->args = pars_join(shell, args, '\"', cmd_index);
	else if (ft_strchr(args, '\'') != NULL)
		shell->cmd[cmd_index]->args = pars_join(shell, args, '\'', cmd_index);
	else
		shell->cmd[cmd_index]->args = ft_split(args, ' ');
	shell->cmd[cmd_index]->args_count = args_counter(
			shell->cmd[cmd_index]->args);
	shell->cmd_count++;
	ft_free_multi_tab(tmp);
}
