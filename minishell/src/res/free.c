/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 01:50:22 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/15 01:52:24 by jmartin          ###   ########.fr       */
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

	i = -1;
	while (ptr[++i])
		ft_free_tab(ptr[i]);
	if (ptr)
		free(ptr);
}
