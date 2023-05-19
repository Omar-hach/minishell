/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_abs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:53:13 by ohachami          #+#    #+#             */
/*   Updated: 2022/11/04 17:56:21 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_putnbr_abs(unsigned int dec, char flag, char c, unsigned int base)
{
	int		degit;
	char	printer;

	degit = 1;
	if (flag == '#' && dec != 0)
	{
		write(2, "0", 1);
		printer = 'x' * (c == 'x') + 'X' * (c == 'X');
		write(2, &printer, 1);
		degit += 2;
	}
	if (dec < 10)
		printer = dec + '0';
	if (dec > 9 && dec < base)
		printer = dec - 10 + (c == 'x') * 'a' + (c == 'X') * 'A';
	if (dec < base)
		write(2, &printer, 1);
	if (dec > base - 1)
	{
		degit += ft_putnbr_abs(dec / base, '@', c, base);
		ft_putnbr_abs(dec % base, '@', c, base);
	}
	return (degit);
}
