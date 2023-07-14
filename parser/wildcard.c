/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:41:18 by maddou            #+#    #+#             */
/*   Updated: 2023/07/14 00:22:04 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <dirent.h>

int	find_begining_patern(char *entry_name, char *patern, int *i, int *j)
{
	int	c;

	*j = 1;
	(*i)++;
	c = (*i);
	while (patern[*j] != '\0')
	{
		if (patern[*j] != entry_name[*i])
			break ;
		(*j)++;
		(*i)++;
	}
	if (patern[*j] == '\0')
		return (c);
	return (-1);
}

char	*find_entry_center(char *entry_name, char *patern, char k)
{
	char	*entry_center;
	int		i;
	int		j;
	int		c;

	i = 0;
	while (entry_name[i] != '\0')
	{
		if (entry_name[i] == patern[0])
		{
			c = find_begining_patern(entry_name, patern, &i, &j);
			if (c != -1)
				break ;
		}
		i++;
	}
	if (patern[j] == '\0' && (k == 'p' || k == 'l'))
	{
		entry_center = ft_substr(entry_name, c, (ft_strlen(entry_name) - c));
	}
	else if (patern[j] == '\0' && (k == 'f' || k == 'n'))
		entry_center = ft_substr(entry_name, c, (ft_strlen(entry_name) - c));
	free(entry_name);
	return (entry_center);
}

int	calcule_number_word_in_entry_dirent(DIR *openfile, struct dirent *entry,
		int i)
{
	openfile = opendir(".");
	while (1)
	{
		entry = readdir(openfile);
		if (!entry)
			break ;
		i++;
	}
	closedir(openfile);
	return (i);
}

void	fill_wil_in_cmd(t_parser *parser, char *data, t_cmd *cmd, int j)
{
	DIR				*openfile;
	struct dirent	*entry;
	int				i;
	int				*nb_w;

	i = 0;
	i = calcule_number_word_in_entry_dirent(openfile, entry, i);
	nb_w = malloc(sizeof(int *) * i);
	if (!nb_w)
		exit(1);
	nb_w = check_exict_patern(parser, data, nb_w, openfile);
	cmd->dt = cop_current_dt(cmd, j, nb_w, i);
	if (count_nb_newdt(nb_w, i) != 0)
	{
		cmd->dt = fill_wildcard_data(cmd, j, nb_w);
		cmd->dt_nb += count_nb_newdt(nb_w, i) - 1;
	}
	free(nb_w);
}

void	handal_wildcard(t_parser *parser, t_cmd *cmd)
{
	int	j;
	int	i;
	int	copy_dtnb;

	j = 0;
	i = 0;
	copy_dtnb = cmd->dt_nb;
	while (j < copy_dtnb)
	{
		i = 0;
		while (cmd->dt[j].data != NULL && cmd->dt[j].data[i] != '\0')
		{
			if (cmd->dt[j].data[i] == '\'' || cmd->dt[j].data[i] == '\"')
				i = skip_quote(cmd->dt[j].data, i);
			if (cmd->dt[j].data[i] == '*')
				break ;
			i++;
		}
		if (cmd->dt[j].data != NULL && cmd->dt[j].data[i] == '*')
			fill_wil_in_cmd(parser, cmd->dt[j].data, cmd, j);
		j++;
	}
}
