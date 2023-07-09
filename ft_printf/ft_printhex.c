/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:51:18 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/09 15:32:32 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hex(unsigned int num, char c)
{
	const char	*small;
	const char	*big;

	small = "0123456789abcdef";
	big = "0123456789ABCDEF";
	if (c == 'x')
	{
		write(1, &small[num], 1);
		return (1);
	}
	if (c == 'X')
	{
		write(1, &big[num], 1);
		return (1);
	}
	return (0);
}

int	ft_printhex(unsigned int nb, char c)
{
	int	cnt;

	cnt = 0;
	if (nb >= 0 && nb < 16)
		cnt += ft_hex(nb, c);
	if (nb >= 16)
	{
		cnt += ft_printhex(nb / 16, c);
		cnt += ft_printhex(nb % 16, c);
	}
	return (cnt);
}
