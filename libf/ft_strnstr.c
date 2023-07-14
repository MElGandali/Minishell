/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:12:49 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/13 18:44:24 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	skip_quotes(char *line, int i)
{
	if (line[i] == '\"')
	{
		i++;
		while (line[i] != '\"')
			i++;
	}
	else if (line[i] == '\'')
	{
		i++;
		while (line[i] != '\'')
			i++;
	}
	return (i);
}

int	ft_strnstr(char *h, char *n)
{
	int	i;
	int	j;

	i = 0;
	if (h == 0 && n)
		return (1);
	while (h[i])
	{
		j = 0;
		if (h[i + j] == '\"' || h[i + j] == '\'')
			i = skip_quotes(h, i + j);
		while (h[i + j] == n[j])
		{
			j++;
			if (n[j] == '\0')
				return (0);
		}
		i++;
	}
	return (1);
}
