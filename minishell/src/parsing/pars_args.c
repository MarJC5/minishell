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

char	*ft_join_quote(t_shell *shell, int cmd_index, int *i)
{
	char	*tmp;
	char	*merge;
	int		c;

	c = 0;
	tmp = ft_strdup("");
	while (*i < args_counter(shell->cmd[cmd_index]->args) - 1 && c == 0)
	{
		if (shell->sq != '\'')
			pars_dollars(shell, cmd_index, *i, NULL);
		quote_finder_two(shell, shell->cmd[cmd_index]->args[*i], 1);
		if (shell->eq != '\0')
			c = 1;
		merge = ft_strjoin(tmp, shell->cmd[cmd_index]->args[*i]);
		free(tmp);
		tmp = ft_strdup(merge);
		free(merge);
		*i += 1;
	}
	return (tmp);
}

void	pars_args_split(t_shell *shell, char *args, int cmd_index)
{
	int	i;

	i = 0;
	if (ft_strchr(args, '\'') || ft_strchr(args, '\"'))
	{
		shell->cmd[cmd_index]->args = ft_split_with_delimiter(args, ' ');
		if (quote_counter_sign(shell->cmd[cmd_index]->args, 0, 0, 0) == '\0')
			shell->cmd[cmd_index]->args = pars_space(shell, 0, 0, cmd_index);
		else
			str_err("minishell: Erreur missing quote\n", &shell->sq);
	}
	else
	{
		shell->cmd[cmd_index]->args = ft_split(args, ' ');
		while (shell->cmd[cmd_index]->args[i])
			pars_dollars(shell, cmd_index, i++, NULL);
	}
}

void	pars_args(t_shell *shell, char *args, int cmd_index)
{
	char	**tmp;

	tmp = ft_split(args, ' ');
	shell->cmd[cmd_index] = malloc(sizeof(t_cmd));
	shell->cmd[cmd_index]->shell = shell;
	shell->cmd[cmd_index]->in = -1;
	shell->cmd[cmd_index]->out = -1;
	shell->cmd[cmd_index]->heredoc = 0;
	shell->cmd[cmd_index]->pid = -1;
	shell->cmd[cmd_index]->cmd_pos = cmd_index;
	shell->cmd[cmd_index]->quotted = 0;
	shell->cmd[cmd_index]->name = ft_strdup(tmp[0]);
	pars_cmd_name_quote(shell->cmd[cmd_index]->name);
	pars_args_split(shell, args, cmd_index);
	shell->cmd[cmd_index]->args_count = args_counter(
			shell->cmd[cmd_index]->args);
	shell->cmd_count++;
	ft_free_multi_tab(tmp);
}
