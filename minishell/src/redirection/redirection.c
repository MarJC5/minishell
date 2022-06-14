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
	(void)shell;
	(void)cmd_index;
	(void)i;
	(void)j;
	/*char	**str;
	int		count;
	int		i2;

	str = NULL;
	count = 0;
	i2 = 0;
	while (shell->cmd[cmd_index]->args[count])
		count++;
	str = calloc((count), sizeof(char *));
	count = 0;
	while (shell->cmd[cmd_index]->args[count])
	{
		if (count == shell->i)
		{
			if (j != 0 && !shell->cmd[cmd_index]->args[i][j])
			{
				i++;
				j = 0;
			}
			//str[i2++] = ft_strdup(&shell->cmd[cmd_index]->args[i][j]);
			shell->cmd[cmd_index]->args[i][j] = '\0';
			count = i + 1;
		}
		else
			(shell->cmd[cmd_index]->args[count++]) = NULL;
		//str[i2++] = ft_strdup(shell->cmd[cmd_index]->args[count++]);
	}

	shell->cmd[cmd_index]->args = str;
	int l = 0;
	while (shell->cmd[cmd_index]->args[l])
		printf("%s ", shell->cmd[cmd_index]->args[l++]);*/
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
