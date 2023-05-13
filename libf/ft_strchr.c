/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:17:44 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/13 11:58:59 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	// if (c == 0)
	// 	return ((char *)s + ft_strlen(s));
	while (s[i])
	{
		if ((char)c == s[i])
			return (0);
		i++;
	}
	return (1);
}
