/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:20:44 by tpaquier          #+#    #+#             */
/*   Updated: 2022/06/08 15:42:15 by jmartin          ###   ########.fr       */
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

int	check_dir(char **path, char *str, struct dirent *file)
{
	if (ft_strcmp(file->d_name, str) == 0)
	{
		ft_free_multi_tab(path);
		return (1);
	}
	return (0);
}

char	*bin_chek(char **split, char *str)
{
	if (ft_strncmp(str, "/bin/", 5) == 0)
	{
		str = ft_strdup(split[1]);
		ft_free_multi_tab(split);
	}
	return (str);
}

int	dir_exist(t_shell *shell, char *str, int i)
{
	DIR				*dir;
	struct dirent	*file;
	char			**path;

	str = bin_chek(ft_split(str, '/'), str);
	path = path_finder(shell);
	while (path[++i])
	{
		dir = opendir(path[i]);
		if (dir != NULL)
		{
			file = readdir(dir);
			while (file != NULL)
			{
				if (check_dir(path, str, file) != 1)
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
