/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:45:11 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/31 09:25:23 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redirection(t_shell *shell, char **args)
{
	int		fd;
	char	*name;
	char	*temp;
	char	cwd[PATH_MAX];

	name = NULL;
	isrediorpipe(shell, args, '>');
	name = getname(args, shell->i, shell->j);
	temp = ft_strjoin(getcwd(cwd, sizeof(cwd)), name);
	free(name);
	name = temp;
	if (isdoubleredi(args, '>') == 2)
		fd = open(name, O_CREAT | O_RDWR | O_APPEND, 0666);
	else
		fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	free(name);
}
