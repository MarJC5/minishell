/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:45:11 by jmartin           #+#    #+#             */
/*   Updated: 2022/04/11 14:45:57 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redirection(t_shell *shell, char **args)
{
	int		i;
	int		fd;
	char	*name;

	i = -1;
	isrediorpipe(shell, args, '>');
	name = getname(args, shell->i, shell->j);
	if (isdoubleredi(args, '>') == 2)
		fd = open(name, O_CREAT | O_RDWR | O_APPEND, 0666);
	else
		fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	dup2(fd, shell->fd);
	free(name);
}
