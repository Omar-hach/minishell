/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 10:21:31 by ohachami          #+#    #+#             */
/*   Updated: 2022/11/04 18:05:48 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	convertion_check(char sign, char flag, va_list args)
{
	int	len;

	len = 1;
	if (sign == 'd' || sign == 'i')
		len = ft_putnbr(va_arg(args, int), flag);
	else if (sign == 's')
		len = ft_putstr(va_arg(args, char *));
	else if (sign == 'c')
		len = ft_putchar((char)va_arg(args, int));
	else if (sign == 'p')
		len = ft_address(va_arg(args, unsigned long), 1) + 2;
	else if (sign == 'u')
		len = ft_putnbr_abs(va_arg(args, unsigned int), '@', 'u', 10);
	else if (sign == 'x')
		len = ft_putnbr_abs(va_arg(args, unsigned int), flag, 'x', 16);
	else if (sign == 'X')
		len = ft_putnbr_abs(va_arg(args, unsigned int), flag, 'X', 16);
	else
		write(1, &sign, 1);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		i;

	va_start(args, format);
	len = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[++i] == ' ' || format[i] == '+' || format[i] == '#')
			{
				len += convertion_check(format[i + 1], format[i], args);
				i++;
			}
			else
				len += convertion_check(format[i], '@', args);
		}
		else
			len += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (len);
}
