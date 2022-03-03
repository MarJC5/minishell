/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:16:18 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/03 14:27:24 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Args counter for malloc size
 *
 * @param args
 * @return int
 */

static int	args_counter(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

/**
 * @brief Set the envp object
 *
 * @param shell
 * @param envp
 */

void	set_envp(t_shell *shell, char **envp)
{
	int	i;

	i = -1;
	if (!shell->envp)
	{
		shell->envp = malloc(args_counter(envp) * sizeof(char *));
		while (++i < args_counter(envp))
			shell->envp[i] = ft_strdup(envp[i]);
	}
}

/**
 * @brief Save a command and his agruments passed through user input
 *
 * @param command
 * @param args
 * @param size
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
		shell->cmd->args = malloc((size) * sizeof(char *));
	if (!shell->cmd->args)
		return (NULL);
	if (args[start])
	{
		shell->cmd->name = ft_strdup(args[1]);
		shell->cmd->args_count = size - start;
	}
	while (args[i])
		shell->cmd->args[j++] = args[i++];
	shell->cmd->args[j] = "\0";
	return (shell->cmd->name);
}
