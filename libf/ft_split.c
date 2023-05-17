/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:07:53 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/17 18:11:29 by maddou           ###   ########.fr       */
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

char	**ft_split(char const *s, char c, int *word_nb)
{
	char	**newstring;
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	*word_nb = ft_word_count(s, c);
	newstring = malloc((/*ft_word_count(s, c)*/*word_nb + 1) * sizeof(char *));
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
