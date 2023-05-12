/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:01:04 by mel-gand          #+#    #+#             */
/*   Updated: 2022/10/19 15:01:38 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_len(long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		len++;
	while (nb)
	{
		if (nb > 0)
		{
			nb = nb / 10;
			len++;
		}
		else if (nb < 0)
		{
			nb *= -1;
			nb = nb / 10;
			len = len + 2;
		}
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	int		len;

	num = (long)n;
	str = malloc(ft_num_len(num) + 1);
	if (!str)
		return (NULL);
	len = ft_num_len(num);
	str[len--] = '\0';
	if (num == 0)
		str[0] = '0';
	else if (num < 0)
	{
		num *= -1;
		str[0] = '-';
	}
	while (num > 0)
	{
		str[len--] = num % 10 + '0';
		num = num / 10;
	}
	return (str);
}
