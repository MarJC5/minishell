/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 09:27:32 by jmartin           #+#    #+#             */
/*   Updated: 2022/04/11 15:06:36 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pwd(t_shell *shell, int cmd_index)
{
	char	cwd[PATH_MAX];

	if (shell->cmd[cmd_index]->args_count > 1)
		str_err("pwd: too many arguments", NULL);
	else
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			ft_printf("%s", cwd);
		else
			perror("getcwd() error");
	}
}
