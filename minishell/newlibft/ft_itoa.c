/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaquier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 08:57:24 by tpaquier          #+#    #+#             */
/*   Updated: 2021/10/21 14:57:36 by tpaquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_itoa_neg(int a)
{
	if (a < 0)
	{
		return (1);
	}
	return (0);
}

static int	ft_itoa_count(int d)
{
	int	c2;

	c2 = 0;
	if (d == 0)
		c2++;
	if (d < 0)
	{
		d = d * -1;
		c2++;
	}
	while (d > 0)
	{
		d = d / 10;
		c2++;
	}
	return (c2);
}

char	*ft_itoa(int n)
{
	int		c;
	int		b;
	int		sign;
	char	*mem;

	sign = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	c = ft_itoa_count(n);
	if (ft_itoa_neg(n) == 1)
		n = n * -1;
	mem = malloc(sizeof(char) * c + 1);
	if (!mem)
		return (NULL);
	mem[c] = '\0';
	b = 0;
	while (c-- > 0)
	{
		b = (n % 10) + '0';
		n = n / 10;
		mem[c] = b;
	}
	if (ft_itoa_neg(sign) == 1)
		mem[0] = '-';
	return (mem);
}
