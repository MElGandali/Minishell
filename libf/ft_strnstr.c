/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:12:49 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/13 18:37:56 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int skip_quotes(char *line, int i)
{
    if (line[i] == '\"'/*34*/)
    {
        i++;
        while (line[i] != '\"'/*34*/)
            i++;
    }
    else if (line[i] == '\''/*39*/)
    {
        i++;
        while (line[i] != '\''/*39*/)
            i++;
    }
    return (i);
}

int ft_strnstr(char *h, char *n)
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
			else if (n[j] != h[i + j])
				return (1);
		}
		i++;
	}
	return (1);
}
