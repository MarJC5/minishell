/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:53:58 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/02 12:48:21 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_export(int args_count, char *cmd, char *args_value, char **list);

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 2)
		get_export(argc, argv[1], argv[2], envp);
	return (0);
}
