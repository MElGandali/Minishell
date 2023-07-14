/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_number_newword_in_one_arg.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:20:40 by maddou            #+#    #+#             */
/*   Updated: 2023/07/14 01:20:53 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_nb_newdt(int *nb_w, int i)
{
	int	j;
	int	nb;

	j = 0;
	nb = 0;
	while (j < i)
	{
		if (nb_w[j] == 1)
			nb++;
		j++;
	}
	return (nb);
}

void	initialization_new_dt(int j, int k, t_data *new_dt, t_cmd *cmd)
{
	if (k != j)
	{
		new_dt[k].data = ft_strdup(cmd->dt[k].data);
		new_dt[k].copy_data = ft_strdup(cmd->dt[k].copy_data);
		new_dt[k].ex_dollar = cmd->dt[k].ex_dollar;
		new_dt[k].name = cmd->dt[k].name;
	}
	free(cmd->dt[k].data);
	free(cmd->dt[k].copy_data);
}

t_data	*cop_current_dt(t_cmd *cmd, int j, int *nb_w, int i)
{
	int		nb;
	t_data	*new_dt;
	int		k;

	nb = count_nb_newdt(nb_w, i);
	k = 0;
	new_dt = NULL;
	if (nb >= 1)
	{
		new_dt = malloc(sizeof(t_data) * (cmd->dt_nb + nb - 1));
		if (!new_dt)
			exit(1);
		while (k < cmd->dt_nb)
		{
			initialization_new_dt(j, k, new_dt, cmd);
			k++;
		}
		free(cmd->dt);
	}
	if (nb == 0)
		return (cmd->dt);
	return (new_dt);
}

int	*find_patern_one_etoile(int *nb_w, char c, char **patern)
{
	int				j;
	DIR				*openfile;
	struct dirent	*entry;

	j = 0;
	openfile = opendir(".");
	while (1)
	{
		entry = readdir(openfile);
		if (!entry)
			break ;
		if (check_valid_first(entry->d_name, patern[0]) == 1 && c == 'f')
			nb_w[j] = 1;
		else if (check_valid_last(entry->d_name, patern[0]) == 1 && c == 'l')
			nb_w[j] = 1;
		else
			nb_w[j] = 0;
		j++;
	}
	closedir(openfile);
	return (nb_w);
}

int	*find_number_w_one_arg(char *data, int *nb_w, char **patern)
{
	if (check_position_etoile(data, 'o') == 1)
		nb_w = find_patern_one_etoile(nb_w, 'l', patern);
	if (check_position_etoile(data, 'o') == 0)
		nb_w = find_patern_one_etoile(nb_w, 'f', patern);
	return (nb_w);
}
