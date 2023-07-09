/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:56:09 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/09 15:32:32 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle(va_list arg, char c)
{
	int	cnt;

	cnt = 0;
	if (c == '%')
		cnt += ft_printchar('%');
	else if (c == 'c')
		cnt += ft_printchar(va_arg(arg, int));
	else if (c == 's')
		cnt += ft_printstr(va_arg(arg, char *));
	else if (c == 'd' || c == 'i')
		cnt = ft_printnbr(va_arg(arg, int));
	if (c == 'u')
		cnt += ft_printuint(va_arg(arg, unsigned int));
	if (c == 'x' || c == 'X')
		cnt += ft_printhex(va_arg(arg, unsigned int), c);
	if (c == 'p')
	{
		cnt += ft_printstr("0x");
		cnt += ft_printpi(va_arg(arg, unsigned long));
	}
	return (cnt);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		count;
	int		i;

	va_start(arg, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			count += ft_handle(arg, str[i]);
		}
		else
			count += ft_printchar(str[i]);
		i++;
	}
	va_end(arg);
	return (count);
}
