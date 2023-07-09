/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printpi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:18:19 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/09 15:33:59 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

static int	ft_hex(unsigned long num)
{
	const char	*x;

	x = "0123456789abcdef";
	write(1, &x[num], 1);
	return (1);
}

int	ft_printpi(unsigned long nb)
{
	int	cnt;

	cnt = 0;
	if (nb >= 0 && nb < 16)
		cnt += ft_hex(nb);
	if (nb >= 16)
	{
		cnt += ft_printpi(nb / 16);
		cnt += ft_printpi(nb % 16);
	}
	return (cnt);
}
