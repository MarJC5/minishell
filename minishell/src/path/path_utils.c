/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:20:44 by tpaquier          #+#    #+#             */
/*   Updated: 2022/06/13 21:21:36 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**path_finder(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], "PATH=", 5) == 0)
			return (ft_split(ft_strchr(shell->envp[i], '=') + 1, ':'));
		i++;
		if (!shell->envp[i])
		{
			g_exit_stat = 127;
			str_err("minishell: PATH not found", NULL);
			return (NULL);
		}
	}
	return (NULL);
}

void	open_dir(t_shell *shell, char **path, char *str, int cmd_index)
{
	DIR				*dir;
	struct dirent	*file;
	int				i;

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
					g_exit_stat = execve(ft_strjoin(append('\0', path[i], '/'),
								file->d_name), shell->cmd[cmd_index]->args,
							shell->envp);
				}
				file = readdir(dir);
			}
			closedir(dir);
		}
	}
}

int	check_dir(char **path, char *str, struct dirent *file, DIR *dir)
{
	if (ft_strcmp(file->d_name, str) == 0 ||
			access(str, X_OK) == 0)
	{
		ft_free_multi_tab(path);
		closedir(dir);
		return (1);
	}
	return (0);
}

int	dir_exist(t_shell *shell, char *str, int i)
{
	DIR				*dir;
	struct dirent	*file;
	char			**path;

	path = path_finder(shell);
	while (path != NULL && path[++i])
	{
		dir = opendir(path[i]);
		if (dir != NULL)
		{
			file = readdir(dir);
			while (file != NULL)
			{
				if (check_dir(path, str, file, dir) != 1)
					file = readdir(dir);
				else
					return (1);
			}
			closedir(dir);
		}
	}
	ft_free_multi_tab(path);
	return (0);
}
