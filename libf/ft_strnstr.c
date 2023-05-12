/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:12:49 by mel-gand          #+#    #+#             */
/*   Updated: 2022/10/20 16:58:02 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (h == 0 && len == 0 && n)
		return (NULL);
	if (ft_strlen(h) < ft_strlen(n))
		return (0);
	if (n[0] == '\0')
		return ((char *)h);
	while (h[i] && i < len)
	{
		j = 0;
		while (h[i + j] == n[j] && i + j < len)
		{
			j++;
			if (n[j] == '\0')
				return ((char *)&h[i]);
			else if (n[j] != h[i + j])
				return (NULL);
		}
		i++;
	}
	return (0);
}
