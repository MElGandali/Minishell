/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_number_newword_in_mul_arg.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:51:15 by maddou            #+#    #+#             */
/*   Updated: 2023/07/13 23:40:34 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*ft_tout_file(int *nb_w, DIR *openfile, t_parser *parser)
{
	struct dirent	*entry;
	int				j;

	(void)parser;
	j = 0;
	openfile = opendir(".");
	while (1)
	{
		entry = readdir(openfile);
		if (!entry)
			break ;
		if (entry->d_name[0] == '.')
			nb_w[j] = 0;
		else
			nb_w[j] = 1;
		j++;
	}
	closedir(openfile);
	return (nb_w);
}

int	*find_first_list_patern(t_parser *parser, int *nb_w, char **patern)
{
	int				j;
	DIR				*openfile;
	struct dirent	*entry;

	(void)parser;
	j = 0;
	openfile = opendir(".");
	while (1)
	{
		entry = readdir(openfile);
		if (!entry)
			break ;
		if (check_valid_first(entry->d_name, patern[0]) == 1
			&& check_valid_last(entry->d_name, patern[1]) == 1
			&& ft_strlen(entry->d_name) >= ft_strlen(patern[0])
			+ ft_strlen(patern[1]))
			nb_w[j] = 1;
		else
			nb_w[j] = 0;
		j++;
	}
	closedir(openfile);
	return (nb_w);
}

int	*find_number_w_mult_arg(t_parser *parser, int *nb_w, char **patern,
		int nb_arg)
{
	DIR	*openfile;

	if (nb_arg == 2)
		nb_w = find_first_list_patern(parser, nb_w, patern);
	else
		nb_w = ft_tout_file(nb_w, openfile, parser);
	return (nb_w);
}
