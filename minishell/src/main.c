/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:53:58 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/03 09:21:19 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	if (argc >= 2)
		if (ft_strcmp(init_cmd(command, argv, argc), "export") == 0)
			set_export(command, envp);
		if (ft_strcmp(init_cmd(command, argv, argc), "pwd") == 0)
			get_pwd();
	return (0);
}
