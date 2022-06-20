/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 09:27:32 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/20 16:43:20 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pwd(t_shell *shell, int cmd_index)
{
	char	cwd[PATH_MAX];
	(void) cmd_index;
	(void) shell;
	g_exit_stat = 1;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		g_exit_stat = 0;
		ft_printf("%s\n", cwd);
	}
	else
		perror("getcwd() error");
}
