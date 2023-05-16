/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:07:53 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/16 23:49:54 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i + 1])
				i++;
		}
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**newstring;
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	newstring = malloc((ft_word_count(s, c) + 1) * sizeof(char *));
	if (!newstring)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		if (i - start > 0)
			newstring[j++] = ft_substr(s, start, i - start - 1);
	}
	
	newstring[j] = 0;
	return (newstring);
}
