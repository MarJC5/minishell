/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 10:52:05 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/07 10:59:17 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	args_counter(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		;
	return (i);
}

void	*ft_free_multi_tab(char **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
	return (NULL);
}
