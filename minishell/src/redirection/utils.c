/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:45:03 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/31 10:05:49 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	isrediorpipe(t_shell *shell, int cmd_index, char sign)
{
	int	i;
	int	j;

	i = 0;
	while (shell->cmd[cmd_index]->args[i])
	{
		j = 0;
		while (shell->cmd[cmd_index]->args[i][j])
		{
			if (shell->cmd[cmd_index]->args[i][j] == sign)
			{
				shell->i = i;
				shell->j = j;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	isdoubleredi(char **args, char sign)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == sign)
			{
				if (args[i][j + 1] == sign)
					return (2);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_more_redi(char **args, char sign)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == sign)
			{
				count++;
				if (count == 3)
					return (1);
			}
			else
				count = 0;
			j++;
		}
		i++;
	}
	return (0);
}

void	set_var_struct(t_shell *shell, int i, int j, int cmd_index)
{
	shell->cmd[cmd_index]->namei = i;
	shell->cmd[cmd_index]->namej = j;
}

void	ft_redo_char2(char **name)
{
	int	i;
	int	j;

	i = 0;
	while (i < args_counter(name))
	{
		j = 0;
		while (name[i][j])
		{
			if (name[i][j] == 27)
				name[i][j] = '|';
			else if (name[i][j] == 6)
				name[i][j] = '<';
			else if (name[i][j] == 11)
				name[i][j] = '>';
			else if (name[i][j] == 8)
				name[i][j] = '$';
			j++;
		}
		i++;
	}
}

void	ft_redo_char3(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (name[i] == 27)
			name[i] = '|';
		else if (name[i] == 6)
			name[i] = '<';
		else if (name[i] == 11)
			name[i] = '>';
		else if (name[i] == 8)
			name[i] = '$';
		i++;
	}
}

char	**ft_copy_multi(char **str)
{
	char	**ret;
	int		i;

	i = 0;
	ret = ft_calloc(args_counter(str) + 1, sizeof(char *));
	while (i < args_counter(str))
	{
		ret[i] = ft_strdup(str[i]);
		i++;
	}
	ft_redo_char2(ret);
	return (ret);
}

char	*getname(t_shell *shell, int i, int j, int cmd_index)
{
	char	**args;
	char	*name;
	int		g;

	g = 0;
	args = ft_copy_multi(shell->cmd[cmd_index]->args);
	if (args[i][j + 1] && args[i][j + 1] != '>' && args[i][j + 1] != '<')
		name = malloc(ft_strlen(&args[i][++j]) + 2);
	else if ((ft_strlen(args[i]) - j) >= 3 && (args[i][j + 1] == '>'
		|| args[i][j + 1] == '<'))
		name = malloc(ft_strlen(&args[i][j += 2]) + 2);
	else
	{
		if (args[i + 1])
			name = malloc(ft_strlen(args[++i]) + 2);
		else
			return (NULL);
		j = 0;
	}
	name[g++] = '/';
	while (args[i][j] && args[i][j] != '>' && args[i][j] != '<') //dire si args[i][j] dans le tab originelle est egal au meme cara
		name[g++] = args[i][j++];
	name[g] = '\0';
	//ft_redo_char3(name);
	set_var_struct(shell, i, j, cmd_index);
	ft_free_multi_tab(args);
	return (name);
}
