/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:20:44 by tpaquier          #+#    #+#             */
/*   Updated: 2022/05/02 15:28:48 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**path_finder(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		if (shell->envp[i][0] == 'P' && shell->envp[i][1] == 'A'
			&& shell->envp[i][2] == 'T' && shell->envp[i][3] == 'H'
			&& shell->envp[i][4] == '=')
			return (ft_split(ft_strchr(shell->envp[i], '=') + 1, ':'));
		i++;
	}
	return (NULL);
}

void	open_dir(t_shell *shell, char **path, char *str, int cmd_index)
{
	DIR				*dir;
	struct dirent	*file;
	int				i;
	char			*exe;

	i = -1;
	while (path[++i])
	{
		dir = opendir(path[i]);
		if (dir != NULL)
		{
			file = readdir(dir);
			while (file != NULL)
			{
				if (ft_strcmp(file->d_name, str) == 0)
				{
					exe = ft_strjoin(append('\0', path[i], '/'), file->d_name);
					execve(exe, shell->cmd[cmd_index]->args, shell->envp);
					free(exe);
				}
				file = readdir(dir);
			}
		}
		closedir(dir);
	}
}

int	check_dir( DIR *dir, char *str, struct dirent *file)
{
	if (ft_strcmp(file->d_name, str) == 0)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

int	dir_exist(t_shell *shell, char *str)
{
	DIR				*dir;
	struct dirent	*file;
	char			**path;
	int				i;

	i = -1;
	path = path_finder(shell);
	while (path[++i])
	{
		dir = opendir(path[i]);
		if (dir != NULL)
		{
			file = readdir(dir);
			while (file != NULL)
			{
				if (check_dir(dir, str, file) != 1)
					file = readdir(dir);
				else
					return (1);
			}
		}
		closedir(dir);
	}
	free(path);
	return (0);
}
