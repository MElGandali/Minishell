/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:19:51 by mel-gand          #+#    #+#             */
/*   Updated: 2022/10/17 21:59:59 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tri;
	int		len;
	int		j;

	j = 0;
	if (s1 == 0 || set == 0)
		return (NULL);
	while (ft_strchr(set, s1[j]) && s1[j])
		j++;
	if (!s1[j])
		return (ft_substr(s1, 0, 0));
	len = ft_strlen(s1);
	while (len > j && ft_strchr(set, s1[len - 1]))
		len--;
	tri = ft_substr(s1, j, len - j);
	return (tri);
}
