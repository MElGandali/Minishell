/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:33:06 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/15 00:08:58 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_red(t_cmd *comm)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (i < comm->dt_nb)
	{
		if (comm->dt[i].name == 4 || comm->dt[i].name == 5
			|| comm->dt[i].name == 6 || comm->dt[i].name == 7)
			nb++;
		i++;
	}
	return (nb);
}

void	fill_red_utils(t_cmd *comm, int *i, int *j)
{
	comm->red[*j].name = comm->dt[*i].name;
	comm->red[*j].ex_dollar = comm->dt[*i].ex_dollar;
	comm->red[*j].copy_data = ft_strdup(comm->dt[*i].copy_data);
	comm->red[(*j)++].data = ft_strdup(comm->dt[(*i)++].data);
	comm->red[*j].ex_dollar = comm->dt[*i].ex_dollar;
	comm->red[*j].name = comm->dt[*i].name;
}

void	fill_red_data(t_cmd *comm, int i, int j)
{
	int	x;

	x = 0;
	if (comm->dt[i].data != NULL)
	{
		comm->red[j].data = NULL;
		while (comm->dt[i].data[x] != '\0')
		{
			if (comm->dt[i].data[x] == '\'' || comm->dt[i].data[x] == '\"')
				comm->red[j].data = if_quote_fill(comm->dt[i].data, &x,
						comm->red[j].data);
			else
				comm->red[j].data = ft_copier(comm->dt[i].data[x],
						comm->red[j].data);
			x++;
		}
	}
	else
		comm->red[j].data = NULL;
	if (comm->dt[i].copy_data != NULL)
		comm->red[j].copy_data = ft_strdup(comm->dt[i].copy_data);
	else
		comm->red[j].copy_data = NULL;
}

void	fill_red(t_cmd *comm, int nb)
{
	int	i;
	int	j;

	(void)comm;
	(void)nb;
	i = 0;
	j = 0;
	comm->red = malloc(sizeof(t_red) * nb);
	while (i < comm->dt_nb)
	{
		if (comm->dt[i].name == 4 || comm->dt[i].name == 5
			|| comm->dt[i].name == 6 || comm->dt[i].name == 7)
		{
			fill_red_utils(comm, &i, &j);
			fill_red_data(comm, i, j);
			j++;
		}
		i++;
	}
}

int	check_red(t_cmd *comm, int i)
{
	if (comm->dt[i].name != 4 && comm->dt[i].name != 5 && comm->dt[i].name != 6
		&& comm->dt[i].name != 7 && comm->dt[i].name != 9
		&& comm->dt[i].name != 10 && comm->dt[i].name != 11)
		return (0);
	return (1);
}
