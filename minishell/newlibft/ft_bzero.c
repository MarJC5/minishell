/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaquier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 08:58:33 by tpaquier          #+#    #+#             */
/*   Updated: 2021/10/20 08:58:35 by tpaquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*s2;

	s2 = (char *)s;
	while (n > 0)
	{
		*s2 = 0;
		s2++;
		n--;
	}
}
