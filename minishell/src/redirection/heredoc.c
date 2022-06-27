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

char	*ft_get_keyword(t_shell *shell, char **str, int cmd_index)
{
	char	*name;
	int		g;
	int		i;
	int		j;

	g = 0;
	i = shell->i;
	j = shell->j;
	isrediorpipe(shell, cmd_index, '<');
	if (ft_strlen(str[i]) - (j + 2) >= 1)
		name = malloc(ft_strlen(&str[i][j += 2]) + 1);
	else if (str[shell->i + 1])
		name = malloc(ft_strlen(str[++i]) + 1);
	while (str[i][j] && str[i][j] != '>' && str[i][j] != '<')
		name[g++] = str[i][j++];
	name[g] = '\0';
	shell->cmd[cmd_index]->namei = i;
	shell->cmd[cmd_index]->namej = j;
	return (name);
}

void	while_heredoc(t_shell *shell, char *kw, int cmd_index)
{
	char	*hline;

	hline = NULL;
	while (1)
	{
		hline = readline("> ");
		if (ft_strcmp(kw, hline) == 0)
		{
			ft_free_tab(hline);
			break ;
		}
		ft_putendl_fd(hline, shell->cmd[cmd_index]->in);
		ft_free_tab(hline);
	}
}

void	ft_cmd_name_changer_eco_line_heredoc(t_shell *shell, int cmd_index)
{
	ft_cmd_name_changer(shell, cmd_index);
	dir_exist(shell, cmd_index);
}

void	heredoc(t_shell *shell, int cmd_index)
{
	char	*kw;

	kw = NULL;
	shell->cmd[cmd_index]->in = open("temp_minishell",
			O_CREAT | O_RDWR | O_APPEND, 0666);
	shell->heredoc = 1;
	kw = ft_get_keyword(shell, shell->cmd[cmd_index]->args, cmd_index);
	while_heredoc(shell, kw, cmd_index);
	ft_free_tab(kw);
	shell->cmd[cmd_index]->args = redirection_arg(shell, cmd_index,
			shell->cmd[cmd_index]->namei, shell->cmd[cmd_index]->namej);
	if (isdoubleredi(shell->cmd[cmd_index]->args, '<') == 2)
	{
		close(shell->cmd[cmd_index]->in);
		unlink("temp_minishell");
		heredoc(shell, cmd_index);
	}
	if (ft_strchr(shell->cmd[cmd_index]->name, '<'))
		ft_cmd_name_changer_eco_line_heredoc(shell, cmd_index);
	close(shell->cmd[cmd_index]->in);
	shell->cmd[cmd_index]->in = open("temp_minishell", O_RDONLY);
	dup2(shell->cmd[cmd_index]->in, STDIN_FILENO);
	close(shell->cmd[cmd_index]->in);
}
