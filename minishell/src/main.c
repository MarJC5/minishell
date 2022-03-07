/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:53:58 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/07 10:59:39 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		i;

	shell = malloc(sizeof(t_shell));
	shell->cmd = malloc(sizeof(t_cmd));
	set_envp(shell, envp);
	if (argc >= 2)
	{
		if (ft_strcmp(init_cmd(shell, argv, 1), "export") == 0)
			set_export(shell);
		if (ft_strcmp(init_cmd(shell, argv, 1), "pwd") == 0)
			get_pwd();
		if (ft_strcmp(init_cmd(shell, argv, 1), "env") == 0)
			get_env(shell);
	}
	ft_free_multi_tab(shell->envp);
	return (0);
}
