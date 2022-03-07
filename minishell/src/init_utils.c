/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:16:18 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/07 08:07:07 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*ft_free_env(char **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
	return (NULL);
}

void	*ft_realloc_env(char **ptr, int size)
{
	int		i;
	char	**ret;

	i = -1;
	ret = malloc(size + 1);
	if (!ret)
		return (NULL);
	while (ptr[++i])
		ft_me
	ret[i] = "\0";
	ft_free_env(ptr);
	return (ret);
}

int	args_counter(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		;
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
		shell->envp = malloc((args_counter(envp) + 1) * sizeof(char *));
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
		shell->cmd->args = malloc((size + 1) * sizeof(char *));
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
