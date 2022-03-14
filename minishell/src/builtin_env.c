/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:42:05 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/14 18:07:06 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	env(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->envp[++i] != NULL)
		ft_printf("%s\n", shell->envp[i]);
}
