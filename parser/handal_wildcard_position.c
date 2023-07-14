/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handal_wildcard_position.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:21:15 by maddou            #+#    #+#             */
/*   Updated: 2023/07/14 00:04:35 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*findnbw_in_fl(char *entry_center, char **patern, int *nb_w, int j)
{
	int	i;

	i = 1;
	while (i < lenght_patern(patern) - 1)
	{
		if (ft_strnstr(entry_center, patern[i]) == 1)
		{
			nb_w[j] = 0;
			free(entry_center);
			break ;
		}
		entry_center = find_entry_center(entry_center, patern[i], 'p');
		i++;
	}
	if (i == lenght_patern(patern) - 1)
	{
		free(entry_center);
		nb_w[j] = 1;
	}
	return (nb_w);
}

int	*findnbw_in_f(char *entry_center, char **patern, int *nb_w, int j)
{
	int	i;

	i = 1;
	while (i < lenght_patern(patern))
	{
		if (ft_strnstr(entry_center, patern[i]) == 1)
		{
			nb_w[j] = 0;
			free(entry_center);
			break ;
		}
		entry_center = find_entry_center(entry_center,
				patern[i],
				'f');
		i++;
	}
	if (i == lenght_patern(patern))
	{
		free(entry_center);
		nb_w[j] = 1;
	}
	return (nb_w);
}

int	*findnbw_in_l(char *entry_center, char **patern, int *nb_w, int j)
{
	int	i;

	i = 0;
	while (i < lenght_patern(patern) - 1)
	{
		if (ft_strnstr(entry_center, patern[i]) == 1)
		{
			nb_w[j] = 0;
			free(entry_center);
			break ;
		}
		entry_center = find_entry_center(entry_center, patern[i], 'l');
		i++;
	}
	if (i == lenght_patern(patern) - 1)
	{
		free(entry_center);
		nb_w[j] = 1;
	}
	return (nb_w);
}

int	*findnbw_in(char *entry_center, char **patern, int *nb_w, int j)
{
	int	i;

	i = 0;
	while (i < lenght_patern(patern))
	{
		if (ft_strnstr(entry_center, patern[i]) == 1)
		{
			nb_w[j] = 0;
			free(entry_center);
			break ;
		}
		entry_center = find_entry_center(entry_center, patern[i], 'n');
		i++;
	}
	if (i == lenght_patern(patern))
	{
		free(entry_center);
		nb_w[j] = 1;
	}
	return (nb_w);
}
