/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:53:58 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/15 09:19:59 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	set_envp(shell, envp);
	init_cmd(shell, argv, 1);
	if (argc >= 2)
	{
		if (ft_strcmp(shell->cmd->name, "unset") == 0)
			unset(shell);
		else if (ft_strcmp(shell->cmd->name, "export") == 0)
			export(shell);
		else if (ft_strcmp(shell->cmd->name, "pwd") == 0)
			pwd();
		else if (ft_strcmp(shell->cmd->name, "env") == 0)
			env(shell);
	}
	return (0);
}
