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

// les " " à gérer pour mon parsing -> espace nom de fichier et caractère NULL des guillement

int		ft_cna(t_shell *shell, int endi, int endj, int cmd_index)
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

char	**redirection_arg(t_shell *shell, int cmd_index, int i, int j)
{
	char	**str;
	char	**tmp;
	int		count;
	int		i2;
	int		cna;
	int		g;
	char	c;

	str = NULL;
	tmp = NULL;
	count = 0;
	i2 = 0;
	g = 0;
	cna = ft_cna(shell, i, j, cmd_index);
	c = shell->cmd[cmd_index]->args[shell->i][shell->j];
	str = ft_calloc(cna, sizeof(char *));
	while (shell->cmd[cmd_index]->args[count])
	{
		if (count != shell->i)
			str[i2++] = ft_strdup(shell->cmd[cmd_index]->args[count++]);
		else
		{
			tmp = ft_split_with_delimiter(shell->cmd[cmd_index]->args[count], c);
			if (shell->j != 0)
				str[i2++] = ft_strdup(tmp[0]);
			if (shell->cmd[cmd_index]->args[i][j])
				str[i2++] = ft_strdup(&shell->cmd[cmd_index]->args[i][j]);
			count = i + 1;
			g = (args_counter(tmp));
			while (g >= 0)
				ft_free_tab(tmp[g--]);
			free(tmp);
		}
	}
	while (count >= 0)
		ft_free_tab(shell->cmd[cmd_index]->args[count--]);
	free(shell->cmd[cmd_index]->args);
	return (str);
}

void	redirection(t_shell *shell, int cmd_index)
{
	char	*name;
	char	*temp;
	char	cwd[PATH_MAX];

	name = NULL;
	shell->cmd[cmd_index]->namei = 0;
	shell->cmd[cmd_index]->namej = 0;
	isrediorpipe(shell, cmd_index, '>');
	name = getname(shell, shell->cmd[cmd_index]->args, shell->i, shell->j, cmd_index);
	temp = ft_strjoin(getcwd(cwd, sizeof(cwd)), name);
	free(name);
	name = temp;
	if (isdoubleredi(shell->cmd[cmd_index]->args, '>') == 2)
		shell->cmd[cmd_index]->out = open(name, O_CREAT | O_RDWR | O_APPEND, 0666);
	else
		shell->cmd[cmd_index]->out = open(name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	dup2(shell->cmd[cmd_index]->out, STDOUT_FILENO);
	close(shell->cmd[cmd_index]->out);
	shell->cmd[cmd_index]->args = redirection_arg(shell, cmd_index,
		shell->cmd[cmd_index]->namei, shell->cmd[cmd_index]->namej);
	free(name);
	if (isrediorpipe(shell, cmd_index, '>') == 1)
		redirection(shell, cmd_index);
}

int	redirection_input(t_shell *shell, int cmd_index)
{
	char	*name;
	char	*temp;
	char	cwd[PATH_MAX];
	int		i;
	
	name = NULL;
	i = 0;
	shell->cmd[cmd_index]->namei = 0;
	shell->cmd[cmd_index]->namej = 0;
	isrediorpipe(shell, cmd_index, '<');
	name = getname(shell, shell->cmd[cmd_index]->args, shell->i, shell->j, cmd_index);
	temp = ft_strjoin(getcwd(cwd, sizeof(cwd)), name);
	free(name);
	name = temp;
	shell->cmd[cmd_index]->in = open(name, O_RDONLY);
	shell->cmd[cmd_index]->args = redirection_arg(shell, cmd_index,
		shell->cmd[cmd_index]->namei, shell->cmd[cmd_index]->namej);
	if (shell->cmd[cmd_index]->in == -1)
	{
		str_err("minishell: file not found: ", name);
		free(name);
		return (1);
	}
	free(name);
	if (isrediorpipe(shell, cmd_index, '<') == 1)
		return(redirection_input(shell, cmd_index));
	dup2(shell->cmd[cmd_index]->in, STDIN_FILENO);
	close(shell->cmd[cmd_index]->in);
	while (i++ < 10000000);
	return (0);
}
