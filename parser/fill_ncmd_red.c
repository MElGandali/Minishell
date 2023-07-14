/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ncmd_red.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:22:55 by maddou            #+#    #+#             */
/*   Updated: 2023/06/06 17:13:39 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_split_newcmd(t_cmd *comm, int *j, char *data)
{
	int	u;
	int	d;

	u = 0;
	d = 0;
	comm->new_cmd[*j] = NULL;
	while (data[d] != '\0' && (data[d] == '\'' || data[d] == '\"'))
		d++;
	if (data[d] == '\0')
		comm->new_cmd[*j] = ft_copier(' ', comm->new_cmd[*j]);
	else
	{
		while (data[u] != '\0')
		{
			if (data[u] == '\'' || data[u] == '\"')
				comm->new_cmd[*j] = if_quote_fill(data, &u, comm->new_cmd[*j]);
			else
				comm->new_cmd[*j] = ft_copier(data[u], comm->new_cmd[*j]);
			u++;
		}
	}
	(*j)++;
}

void	ft_split_data(t_cmd *comm, int i, int *j)
{
	int		word_nb;
	char	**split_data;
	int		c;
	int		k;

	c = 0;
	k = 0;
	// printf ("%d", i);
	while (comm->dt[i].data[c] != '\0')
	{
		if (comm->dt[i].data[c] == '\"' || comm->dt[i].data[c] == '\'')
			c = skip_quote(comm->dt[i].data, c);
		else if (comm->dt[i].data[c] == ' ' || comm->dt[i].data[c] == '\t'
			|| comm->dt[i].data[c] == '\n')
			comm->dt[i].data[c] = '\n';
		c++;
	}
	split_data = ft_split(comm->dt[i].data, '\n', &word_nb);
	// while (split_data[h] != NULL)
	// 	printf ("%s\n", split_data[h++]);
	// printf ("%d\n", *j);
	while (split_data[k] != NULL)
		fill_split_newcmd(comm, j, split_data[k++]);
	// printf ("%d", *j);
	// exit (0);
}

void	fill_newcmd_utils(t_parser *parser, int i, int nb_newcmd)
{
	int	j;

	j = 0;
	while (j < parser->comm[i].dt_nb)
	{
		if (check_red(&parser->comm[i], j) == 0)
			nb_newcmd += count_newcmd(parser->comm[i].dt[j].data);
		j++;
	}
	if (nb_newcmd != 0)
	{
		parser->comm[i].new_cmd = malloc(sizeof(char *) * (nb_newcmd + 1));
		check_and_fill_newcmd(&parser->comm[i]);
	}
	else
		parser->comm[i].new_cmd = NULL;
	// print(parser, parser->comm[i].nb_red, nb_newcmd, i);
}

void	fill_newcmd_red(t_parser *parser)
{
	int	i;
	int	x;
	int	nb_newcmd;

	i = 0;
	while (i < parser->lex->pipe_nb)
	{
		x = 0;
		nb_newcmd = 0;
		parser->comm[i].nb_red = count_red(&parser->comm[i]) * 2;
		if (parser->comm[i].nb_red != 0)
			fill_red(&parser->comm[i], parser->comm[i].nb_red);
		fill_newcmd_utils(parser, i, nb_newcmd);
		i++;
	}
}
