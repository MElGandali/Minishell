/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_newcmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:37:35 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/14 19:01:35 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*if_quote_fill(char *data, int *u, char *new_cmd)
{
	char	c;

	c = data[(*u)];
	(*u)++;
	while (data[*u] != c)
	{
		new_cmd = ft_copier(data[*u], new_cmd);
		(*u)++;
	}
	return (new_cmd);
}

int	count_newcmd(char *data)
{
	int	i;
	int	nb;

	i = 0;
	nb = 1;
	while (data[i] != '\0')
	{
		if (data[i] == '\"' || data[i] == '\'')
			i = skip_quote(data, i);
		if (data[i + 1] != '\0' && data[i] <= 32 && i > 0 && data[i - 1] != 32)
			nb++;
		i++;
	}
	return (nb);
}

int	ft_check_split(char *data)
{
	int	i;

	i = 0;
	while (data[i] != '\0')
	{
		if (data[i] == '\"' || data[i] == '\'')
			i = skip_quote(data, i);
		if (data[i] <= 32)
			return (1);
		i++;
	}
	return (0);
}

void	fill_newcmd(t_cmd *comm, int *j, int i)
{
	int	u;
	int	d;

	u = 0;
	d = 0;
	comm->new_cmd[*j] = NULL;
	while (comm->dt[i].data[d] != '\0' && (comm->dt[i].data[d] == '\''
			|| comm->dt[i].data[d] == '\"'))
		d++;
	if (comm->dt[i].data[d] == '\0')
		comm->new_cmd[*j] = ft_copier(' ', comm->new_cmd[*j]);
	else
	{
		while (comm->dt[i].data[u] != '\0')
		{
			if (comm->dt[i].data[u] == '\'' || comm->dt[i].data[u] == '\"')
				comm->new_cmd[*j] = if_quote_fill(comm->dt[i].data, &u,
						comm->new_cmd[*j]);
			else
				comm->new_cmd[*j] = ft_copier(comm->dt[i].data[u],
						comm->new_cmd[*j]);
			u++;
		}
	}
	(*j)++;
}

void	check_and_fill_newcmd(t_cmd *comm)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < comm->dt_nb)
	{
		if (check_red(comm, i) == 0)
		{
			if (ft_check_split(comm->dt[i].data) == 1)
				ft_split_data(comm, i, &j);
			else
				fill_newcmd(comm, &j, i);
		}
		i++;
	}
	comm->new_cmd[j] = NULL;
}
