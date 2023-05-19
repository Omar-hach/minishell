/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:52:25 by ohachami          #+#    #+#             */
/*   Updated: 2022/11/04 17:53:24 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_printer(int n)
{
	char	printer;
	int		digit;

	digit = 1;
	if (n < 10)
	{
		printer = n + '0';
		write(2, &printer, 1);
	}
	else
	{
		digit += ft_printer(n / 10);
		ft_printer(n % 10);
	}
	return (digit);
}

int	ft_putnbr(int n, char flag)
{
	int		digit;

	digit = 0;
	if (n == -2147483648)
	{
		write(2, "-2147483648", 11);
		return (11);
	}
	if (n >= 0 && (flag == ' ' || flag == '+'))
	{
		write(2, &flag, 1);
		digit++;
	}
	if (n < 0)
	{
		write(2, "-", 1);
		n = (-1) * n;
		digit++;
	}
	digit += ft_printer(n);
	return (digit);
}
