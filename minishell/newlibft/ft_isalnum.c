/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaquier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 08:59:12 by tpaquier          #+#    #+#             */
/*   Updated: 2021/10/20 08:59:16 by tpaquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalnum(int alnum)
{
	if ((alnum >= 'a' && alnum <= 'z') || (alnum >= 'A' && alnum <= 'Z'))
		return (1);
	else if (alnum >= '0' && alnum <= '9')
		return (1);
	else
		return (0);
}
