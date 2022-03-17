/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 09:27:32 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/17 14:59:39 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Get the current pwd object and print it
 */

void	pwd(t_shell *shell)
{
	char	cwd[PATH_MAX];

	if (shell->cmd->args_count > 1)
		str_err("pwd: too many arguments", NULL);
	else
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			ft_printf("%s", cwd);
		else
			perror("getcwd() error");
	}
}
