/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printuint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:03:43 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/09 15:32:32 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printuint(unsigned int nb)
{
	int	cnt;

	cnt = 0;
	if (nb < 0)
	{
		cnt += ft_printchar('-');
		(nb *= -1);
	}
	if (nb >= 0 && nb <= 9)
		cnt += ft_printchar(nb + '0');
	if (nb > 9)
	{
		cnt += ft_printuint(nb / 10);
		cnt += ft_printuint(nb % 10);
	}
	return (cnt);
}
