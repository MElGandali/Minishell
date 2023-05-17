/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:15:42 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/17 15:38:19 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int skip_quote(char *line, int i)
// {
//     if (line[i] == '\"'/*34*/)
//     {
//         i++;
//         while (line[i] != '\"'/*34*/)
//             i++;
//     }
//     else if (line[i] == '\''/*39*/)
//     {
//         i++;
//         while (line[i] != '\''/*39*/)
//             i++;
//     }
//     return (i);
// }

// int 	nos_len(char *s1)
// {
// 	int i;
// 	int  j;

// 	i = 0;
// 	j = 0;
// 	while(s1[i] != '\0')
// 	{
// 		if (s1[i] == '\'' || s1[i] == '\"')
// 			i = skip_quote(s1, i);
// 		while((((s1[i] >= 9 && s1[i] <= 13) || s1[i] == 32 )&& s1[i] != '\n')
// 			&& s1[i + 1] != '\0') 
// 		{
// 			i++;
// 			j++;
// 		}
// 		i++;
// 	}
// 	if (s1[i] == '\0' && s1[i - 1] == ' ')
// 		j += 1;
// 	return (i);
// }

// char	*ft_strdup(const char *s1)
// {
// 	char	*p;
// 	int		i;
// 	int j;
// 	int start;

// 	p = malloc(nos_len((char *)s1) + 1);
// 	if (!p)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	start = 0;
// 	while (s1[i])
// 	{
// 		if (s1[i] == '\'' || s1[i] == '\"')
// 		{
// 			start = i;
// 			i = skip_quote((char *)s1, i);
// 			while (i - start > 0)
// 				p[j++] = (char)s1[start++];
// 		}
// 		while((((s1[i] >= 9 && s1[i] <= 13) || s1[i] == 32 )&& s1[i] != '\n')
// 			&& s1[i + 1] != '\0')
// 				i++;
// 			p[j++] = (char)s1[i];
// 		i++;
// 	}
// 	p[j] = '\0';
// 	return (p);
// }

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*p;
	int		i;

	len = ft_strlen(s1);
	p = malloc(len + 1);
	i = 0;
	if (!p)
		return (NULL);
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}