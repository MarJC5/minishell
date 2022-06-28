/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:20:44 by tpaquier          #+#    #+#             */
/*   Updated: 2022/06/21 16:45:35 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**path_finder(t_shell *shell)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], "PATH=", 5) == 0)
		{
			tmp = ft_split(ft_strchr(shell->envp[i], '=') + 1, ':');
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

static void	ft_free_dir(char *acctmp, char **path)
{
	ft_free_tab(acctmp);
	ft_free_multi_tab(path);
}

static void	swap_cmd_name(t_shell *shell, int cmd_index, char *path, char *new)
{
	new = ft_strdup(shell->cmd[cmd_index]->name);
	free(shell->cmd[cmd_index]->name);
	shell->cmd[cmd_index]->name = NULL;
	shell->cmd[cmd_index]->name = ft_strjoin(path, new);
	free(new);
	new = NULL;
}

int	dir_exist(t_shell *shell, int cmd_index, char *tmp, char *acctmp)
{
	char	**path;
	int		i;

	i = -1;
	if (path_exist(shell->envp, shell->cmd[cmd_index]->name) == 1)
		return (0);
	if (path_exist(shell->envp, shell->cmd[cmd_index]->name) == 2)
		return (1);
	path = path_finder(shell);
	while (path[++i])
	{
		if (ft_strchr(shell->cmd[cmd_index]->name, '/'))
			return (1);
		acctmp = ft_strjoin(append('\0', path[i], '/'),
				shell->cmd[cmd_index]->name);
		if (access(acctmp, (X_OK)) == 0)
		{
			swap_cmd_name(shell, cmd_index, path[i], tmp);
			ft_free_dir(acctmp, path);
			return (1);
		}
		ft_free_tab(acctmp);
	}
	ft_free_multi_tab(path);
	return (0);
}
