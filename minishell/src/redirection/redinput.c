/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redinput.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:45:11 by jmartin           #+#    #+#             */
/*   Updated: 2022/07/01 09:40:07 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_err_redinput(char *name, t_shell *shell)
{
	shell->redinput_err = 1;
	str_err("minishell: file not found: ", name);
	free(name);
	return (1);
}

char	*redinput_name(t_shell *shell, int cmd_index)
{
	char	cwd[PATH_MAX];
	char	*name;
	char	*temp;

	temp = NULL;
	name = NULL;
	name = getname(shell, shell->i, shell->j, cmd_index);
	temp = ft_strjoin(getcwd(cwd, sizeof(cwd)), name);
	free(name);
	name = temp;
	return (name);
}

void	ft_cmd_name_changer_eco_line(t_shell *shell, int cmd_index)
{
	if (!shell->cmd[cmd_index]->args[0])
		return ;
	ft_cmd_name_changer(shell, cmd_index);
	dir_exist(shell, cmd_index, NULL, NULL);
}

int	ret_err_redinput(char *name)
{
	str_err("minishell: syntax error near unexpected token `newline'", NULL);
	free(name);
	return (1);
}

int	redirection_input(t_shell *shell, int cmd_index)
{
	char	*name;
	int		i;

	i = 0;
	name = reset_redinput(shell, cmd_index);
	isrediorpipe(shell, cmd_index, '<');
	name = redinput_name(shell, cmd_index);
	if (name == NULL)
		return (ret_err_redinput(name));
	shell->cmd[cmd_index]->in = open(name, O_RDONLY);
	dup2(shell->cmd[cmd_index]->in, STDIN_FILENO);
	if (shell->cmd[cmd_index]->in != -1)
		close(shell->cmd[cmd_index]->in);
	shell->cmd[cmd_index]->args = redirection_arg(shell, cmd_index,
			shell->cmd[cmd_index]->namei, shell->cmd[cmd_index]->namej);
	if (ft_strchr(shell->cmd[cmd_index]->name, '<'))
		ft_cmd_name_changer_eco_line(shell, cmd_index);
	if (shell->cmd[cmd_index]->in == -1)
		return (ft_err_redinput(name, shell));
	free(name);
	if (isrediorpipe(shell, cmd_index, '<') == 1)
		redirection_input(shell, cmd_index);
	while (i++ < 10000000)
		;
	return (0);
}
