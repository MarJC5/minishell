/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:16:18 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/15 02:03:14 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Save user command to proceed them in the correct order
 *
 * @param shell
 * @param args
 * @param start
 * @return char*
 */

char	*init_cmd(t_shell *shell, char **args, int start)
{
	int	i;
	int	j;
	int	size;

	i = 2;
	j = 0;
	size = args_counter(args);
	if (size > 1)
		shell->cmd.args = malloc((size + 1) * sizeof(char *));
	if (!shell->cmd.args)
		return (NULL);
	if (args[start])
	{
		shell->cmd.name = ft_strdup(args[1]);
		shell->cmd.args_count = size - start;
	}
	while (args[i])
		shell->cmd.args[j++] = args[i++];
	shell->cmd.args[j] = "\0";
	return (shell->cmd.name);
}
