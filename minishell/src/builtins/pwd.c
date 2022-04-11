/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 09:27:32 by jmartin           #+#    #+#             */
/*   Updated: 2022/04/11 07:36:43 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Get the current pwd object and print it
 */

int	wherepwd(t_shell *shell)
{
	int		i;

	i = 0;
	while(shell->cmd->args[i])
	{
		if (shell->cmd->args[i][0] == 'p' && shell->cmd->args[i][1] == 'w'
			&& shell->cmd->args[i][2] == 'd')
			return (i + 1);
		i++;
	}
	return (-1);
}

void	pwd(t_shell *shell)
{
	char	cwd[PATH_MAX];

	if (shell->cmd->args_count > 1 && shell->cmd->args[wherepwd(shell)][0] != '>')
		str_err("pwd: too many arguments", NULL);
	else
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			if (isrediorpipe(shell, '>') == 1)
			{
				shell->cmd->pwd = cwd;
				redirection(shell, 2);
			}
			else
				ft_printf("%s", cwd);
		}
		else
			perror("getcwd() error");
	}
}
