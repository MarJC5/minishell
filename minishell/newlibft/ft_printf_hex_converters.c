/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex_converters.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaquier <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:00:21 by tpaquier          #+#    #+#             */
/*   Updated: 2021/11/11 10:00:21 by tpaquier         ###   Lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hexconverter(unsigned int dec)
{
	unsigned int	temp;

	temp = dec % 16;
	if (temp < 10)
		temp += 48;
	else if (temp >= 10)
		temp = temp + 55;
	if ((dec / 16) != 0)
		ft_hexconverter(dec / 16);
	write(1, &temp, 1);
	temp = 0;
	return (0);
}

int	ft_hexconverter_min(unsigned int dec)
{
	unsigned int	mem;

	mem = dec % 16;
	if (mem < 10)
		mem += 48;
	else if (mem >= 10)
		mem += 87;
	if ((dec / 16) != 0)
		ft_hexconverter_min(dec / 16);
	write(1, &mem, 1);
	mem = 0;
	return (0);
}

int	ft_hexconverter_ptr(unsigned long dec, int *byte)
{
	unsigned long	mem;

	mem = dec % 16;
	if (mem < 10)
	{
		*byte += 1;
		mem += 48;
	}
	else if (mem >= 10)
	{
		*byte += 1;
		mem += 87;
	}
	if ((dec / 16) != 0)
		ft_hexconverter_ptr(dec / 16, &*byte);
	write(1, &mem, 1);
	mem = 0;
	return (0);
}

int	ft_hex_a(va_list arg, int b)
{
	unsigned int	a;

	a = va_arg(arg, unsigned int);
	b = ft_hexconverter_min(a);
	if (a == 0 || a < 0)
	{
		a *= -1;
		b++;
	}
	while (a > 0)
	{
		a /= 16;
		b++;
	}
	return (b);
}

int	ft_hex_b(va_list arg, int b)
{
	unsigned int	a;

	a = va_arg(arg, unsigned int);
	b = ft_hexconverter(a);
	if (a == 0 || a < 0)
	{
		a *= -1;
		b++;
	}
	while (a > 0)
	{
		a /= 16;
		b++;
	}
	return (b);
}
