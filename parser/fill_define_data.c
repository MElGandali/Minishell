/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_define_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:16:04 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/13 17:58:06 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	define_data_utils(t_cmd *comm, char *data, int pos)
{
	if ((comm->dt[pos - 1].name == DOC || comm->dt[pos - 1].name == DELIMITER)
		&& comm->nb_cmd == 0 && data[0] != '<' && data[0] != '>')
	{
		comm->nb_cmd = 1;
		comm->dt[pos].name = COMMAND;
	}
	else if (find_data_redir(&comm->dt[pos - 1].name, comm->dt[pos
				- 1].data) == 0)
	{
		if (comm->dt[pos - 1].name == HERE_DOC)
			comm->dt[pos].name = DELIMITER;
		else
			comm->dt[pos].name = DOC;
	}
	else if (find_data_redir(&comm->dt[pos].name, data) == 0)
		return ;
	else
		comm->dt[pos].name = WORD;
}

void	define_data(t_cmd *comm, char *data, int pos)
{
	if (pos == 0)
	{
		if (find_data_redir(&comm->dt[0].name, data) == 0)
			return ;
		else
		{
			comm->nb_cmd = 1;
			comm->dt[0].name = COMMAND;
		}
	}
	else
		check_pos_one(comm, data, pos);
	if (pos > 1)
		define_data_utils(comm, data, pos);
}

void	fill_data(t_cmd comm)
{
	int	i;

	i = 0;
	while (i < comm.dt_nb)
	{
		comm.dt[i].data = ft_substr(comm.cmd[i], 0, ft_strlen(comm.cmd[i]));
		comm.dt[i].copy_data = ft_substr(comm.cmd[i], 0,
				ft_strlen(comm.cmd[i]));
		define_data(&comm, comm.dt[i].data, i);
		if (i == 0 || (i > 0 && ft_strcmp("<<", comm.dt[i - 1].data) != 0))
			comm.dt[i].ex_dollar = check_ex_dollar(comm.dt[i].data);
		else if (i > 0 && ft_strcmp("<<", comm.dt[i - 1].data) == 0)
		{
			if (ft_check_expand_delimiter(comm.dt[i].data) == 1)
				comm.dt[i].ex_dollar = 2;
			else
				comm.dt[i].ex_dollar = 0;
		}
		else
			comm.dt[i].ex_dollar = 0;
		i++;
	}
}
