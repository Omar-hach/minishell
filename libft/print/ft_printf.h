/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:04:57 by ohachami          #+#    #+#             */
/*   Updated: 2022/10/23 01:57:05 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include<stdarg.h>
# include<unistd.h>

int		ft_printf(const char *format, ...);
int		ft_putnbr_abs(unsigned int dec, char flag, char c, unsigned int base);
int		ft_address(unsigned long adr, int detect);
int		ft_putnbr(int n, char flag);
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_strlen(const char *str);

#endif
