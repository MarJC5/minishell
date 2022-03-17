/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 01:50:22 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/17 21:04:04 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_free_tab(char *ptr)
{
	if (ptr)
		free(ptr);
}

void	ft_free_multi_tab(char **ptr)
{
	int	i;

	i = 1;
	while (i < args_counter(ptr) & ptr[i] != NULL)
		ft_free_tab(ptr[i++]);
	free(ptr);
}

void	ft_free_read_args(t_shell *shell, char *line)
{
	ft_free_tab(shell->cmd->name);
	ft_free_multi_tab(shell->cmd->args);
	if (shell->cmd)
		free(shell->cmd);
	if (line)
		free(line);
}
