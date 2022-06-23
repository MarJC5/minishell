/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaquier <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:00:21 by tpaquier          #+#    #+#             */
/*   Updated: 2021/11/11 10:00:21 by tpaquier         ###   Lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_char_s(va_list arg, int b, int *byte)
{
	char	*a;

	a = va_arg(arg, char *);
	if (a == NULL)
	{
		ft_putstr_two_fd("(null)", 1, &*byte);
		return (b);
	}
	ft_putstr_two_fd(a, 1, &*byte);
	return (b);
}

int	ft_nbr_di(va_list arg, int b)
{
	long int	a;

	a = va_arg(arg, int);
	ft_putnbr_fd(a, 1);
	if (a < 0 || a == 0)
	{
		a *= -1;
		b++;
	}
	while (a > 0)
	{
		a /= 10;
		b++;
	}
	return (b);
}

int	ft_nbr_u(va_list arg, int b)
{
	unsigned int	a;

	a = va_arg(arg, unsigned int);
	ft_put_unsigned_nbr_fd(a, 1);
	if (a == 0)
	{
		b++;
	}
	while (a > 0)
	{
		a /= 10;
		b++;
	}
	return (b);
}

int	ft_char_c(va_list arg, int b)
{
	char	a;

	b = 1;
	a = va_arg(arg, int);
	ft_putchar_fd(a, 1);
	return (b);
}

int	ft_hex_p(void *a, int b, int *byte)
{
	ft_putstr_two_fd("0x", 1, &*byte);
	b = ft_hexconverter_ptr((unsigned long) a, *&byte);
	return (b);
}
