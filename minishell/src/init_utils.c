/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:16:18 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/03 09:22:42 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Save a command and his agruments passed through user input
 *
 * @param command
 * @param argv
 * @param argc
 * @return char*
 */

char	*init_cmd(t_cmd	*command, char **argv, int argc)
{
	int	i;
	int	j;

	i = 2;
	j = 0;
	command->args = malloc((argc) * sizeof(char *));
	if (!command->args)
		return (NULL);
	if (argv[1])
	{
		command->name = ft_strdup(argv[1]);
		command->args_count = argc - 1;
	}
	while (argv[i])
		command->args[j++] = argv[i++];
	command->args[j] = "\0";
	return (command->name);
}
