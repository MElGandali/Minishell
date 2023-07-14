/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_mult_patern.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:17:33 by maddou            #+#    #+#             */
/*   Updated: 2023/07/14 01:34:16 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*wild_fl(int *nb_w, char *entry_dname, char **patern, int j)
{
	char	*entry_center;

	if (check_valid_first(entry_dname, patern[0]) == 1
		&& check_valid_last(entry_dname, patern[lenght_patern(patern) - 1]) == 1
		&& ft_strlen(entry_dname) >= ft_strlen(patern[0])
		+ ft_strlen(patern[lenght_patern(patern) - 1]))
	{
		entry_center = ft_substr(entry_dname, ft_strlen(patern[0]),
				ft_strlen(entry_dname) - ft_strlen(patern[lenght_patern(patern)
					- 1]) - ft_strlen(patern[0]));
		nb_w = findnbw_in_fl(entry_center, patern, nb_w, j);
	}
	else
		nb_w[j] = 0;
	return (nb_w);
}

int	*wild_f(int *nb_w, char *entry_dname, char **patern, int j)
{
	char	*entry_center;

	if (check_valid_first(entry_dname, patern[0]) == 1
		&& ft_strlen(patern[0]) < ft_strlen(entry_dname))
	{
		entry_center = ft_substr(entry_dname, ft_strlen(patern[0]),
				ft_strlen(entry_dname) - ft_strlen(patern[0]));
		nb_w = findnbw_in_f(entry_center, patern, nb_w, j);
	}
	else
		nb_w[j] = 0;
	return (nb_w);
}

int	*wild_l(int *nb_w, char *entry_dname, char **patern, int j)
{
	char	*entry_center;

	if (check_valid_last(entry_dname, patern[lenght_patern(patern) - 1]) == 1
		&& ft_strlen(patern[lenght_patern(patern)
				- 1]) < ft_strlen(entry_dname))
	{
		entry_center = ft_substr(entry_dname, 0, ft_strlen(entry_dname)
				- ft_strlen(patern[lenght_patern(patern) - 1]));
		nb_w = findnbw_in_l(entry_center, patern, nb_w, j);
	}
	else
		nb_w[j] = 0;
	return (nb_w);
}

int	*wild(char *entry_name, char **patern, int *nb_w, int j)
{
	char	*entry_center;

	entry_center = ft_strdup(entry_name);
	nb_w = findnbw_in(entry_center, patern, nb_w, j);
	return (nb_w);
}

int	*find_mult_etoile(int *nb_w, char *data, char **patern, DIR *openfile)
{
	int				j;
	struct dirent	*entry;

	j = 0;
	openfile = opendir(".");
	while (1)
	{
		entry = readdir(openfile);
		if (!entry)
			break ;
		if (check_position_etoile(data, 'm') == 1)
			nb_w = wild_fl(nb_w, entry->d_name, patern, j);
		else if (check_position_etoile(data, 'm') == 2)
			nb_w = wild_f(nb_w, entry->d_name, patern, j);
		else if (check_position_etoile(data, 'm') == 3)
			nb_w = wild_l(nb_w, entry->d_name, patern, j);
		else if (check_position_etoile(data, 'm') == 4)
			nb_w = wild(entry->d_name, patern, nb_w, j);
		j++;
	}
	closedir(openfile);
	return (nb_w);
}
