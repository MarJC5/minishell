/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaquier <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:00:21 by tpaquier          #+#    #+#             */
/*   Updated: 2021/11/11 10:00:21 by tpaquier         ###   Lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_unsigned_nbr_fd(unsigned int n, int fd)
{
	unsigned int	num;

	num = n;
	if (num <= 9)
		ft_putchar_fd(num + '0', fd);
	else
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putchar_fd(((num % 10) + '0'), fd);
	}
}

void	ft_putstr_two_fd(char *s, int fd, int *byte)
{
	size_t	i;

	i = 0;
	while (s && s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	*byte += i;
}

static int	ft_letter(const char chara, va_list arg, int *byte)
{
	if (chara == 'c')
		return (ft_char_c(arg, 0));
	if (chara == 's')
		return (ft_char_s(arg, 0, &*byte));
	if (chara == 'd' || chara == 'i')
		return (ft_nbr_di(arg, 0));
	if (chara == 'u')
		return (ft_nbr_u(arg, 0));
	if (chara == 'p')
		return (ft_hex_p(va_arg(arg, void *), 0, &*byte));
	if (chara == 'X')
		return (ft_hex_b(arg, 0));
	if (chara == 'x')
		return (ft_hex_a(arg, 0));
	if (chara == '%')
	{
		ft_putchar_fd('%', 1);
		return (1);
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		i;
	int		byte;

	i = 0;
	byte = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			byte += ft_letter(str[i + 1], arg, &byte);
			i++;
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			byte++;
		}
		i++;
	}
	va_end(arg);
	return (byte);
}
