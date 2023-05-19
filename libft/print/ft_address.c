/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_address.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:07:14 by ohachami          #+#    #+#             */
/*   Updated: 2022/11/04 17:51:09 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_address(unsigned long adr, int detect)
{
	int		digit;
	char	printer;

	digit = 1;
	if (digit == detect && adr < 16)
		write(2, "0x", 2);
	if (adr < 10)
		printer = adr + '0';
	if (adr > 9 && adr < 16)
		printer = adr - 10 + 'a';
	if (adr < 16)
		write(2, &printer, 1);
	if (adr > 15)
	{
		digit += ft_address(adr / 16, detect++);
		ft_address(adr % 16, detect++);
	}
	return (digit);
}
