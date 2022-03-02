/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 09:27:32 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/02 10:46:31 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <limits.h>
#include <stdio.h>
#include <errno.h>

/**
 * @brief Get the current pwd object and print it
 *
 * @param cmd
 */

void	get_pwd(char *cmd)
{
	char	cwd[PATH_MAX];

	if (ft_strcmp("pwd", cmd) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			ft_printf("%s", cwd);
		else
			perror("getcwd() error");
	}
}
