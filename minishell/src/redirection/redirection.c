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

void	redirection_arg(t_shell *shell, int cmd_index, int i, int j)
{
	char	**str;
	char	**tmp;
	int		count;
	int		i2;
	int		g;
	char	c;

	str = NULL;
	count = 0;
	i2 = 0;
	g = 0;
	c = shell->cmd[cmd_index]->args[shell->i][shell->j];
	while (shell->cmd[cmd_index]->args[count])
		count++;
	str = ft_calloc((count + 1), sizeof(char *));
	str[count + 1] = NULL;
	count = 0;
	while (shell->cmd[cmd_index]->args[count])
	{
		if (count == shell->i)
		{
			tmp = ft_split_with_delimiter(shell->cmd[cmd_index]->args[count], c);
			if (shell->j != 0)
				str[i2++] = ft_strdup(tmp[0]);
			if (shell->cmd[cmd_index]->args[i][j])
				str[i2++] = ft_strdup(&shell->cmd[cmd_index]->args[i][j]);
			count = i + 1;
			while (tmp[g])
				ft_free_tab(tmp[g++]);
		}
		else
			str[i2++] = ft_strdup(shell->cmd[cmd_index]->args[count++]);
	}
	while (count != 0)
		ft_free_tab(shell->cmd[cmd_index]->args[count--]);
	shell->cmd[cmd_index]->args = str;
}

void	redirection(t_shell *shell, char **args, int cmd_index)
{
	char	*name;
	char	*temp;
	char	cwd[PATH_MAX];

	name = NULL;
	isrediorpipe(shell, args, '>');
	name = getname(shell, args, shell->i, shell->j, cmd_index);
	temp = ft_strjoin(getcwd(cwd, sizeof(cwd)), name);
	free(name);
	name = temp;
	if (isdoubleredi(args, '>') == 2)
		shell->cmd[cmd_index]->out = open(name, O_CREAT | O_RDWR | O_APPEND, 0666);
	else
		shell->cmd[cmd_index]->out = open(name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	dup2(shell->cmd[cmd_index]->out, STDOUT_FILENO);
	close(shell->cmd[cmd_index]->out);
	free(name);
}

void	redirection_input(t_shell *shell, char **args, int cmd_index)
{
	char	*name;
	char	*temp;
	char	cwd[PATH_MAX];

	name = NULL;
	isrediorpipe(shell, args, '<');
	name = getname(shell, args, shell->i, shell->j, cmd_index);
	temp = ft_strjoin(getcwd(cwd, sizeof(cwd)), name);
	free(name);
	name = temp;
	shell->cmd[cmd_index]->in = open(name, O_RDONLY);
	dup2(shell->cmd[cmd_index]->in, STDIN_FILENO);
	close(shell->cmd[cmd_index]->in);
	free(name);
	int i;
	i = 0;
	while (i++ < 10000000);
}
