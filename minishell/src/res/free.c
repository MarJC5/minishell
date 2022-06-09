/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 01:50:22 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/09 09:30:50 by jmartin          ###   ########.fr       */
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

	i = 0;
	while (i <= args_counter(ptr) && ptr[i] != NULL)
		ft_free_tab(ptr[i++]);
	free(ptr);
}

void	ft_free_read_args(t_shell *shell, char *line)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count)
		ft_free_multi_tab(shell->cmd[i++]->args);
	if (shell->cmd)
		free(shell->cmd);
	if (line)
		free(line);
}
