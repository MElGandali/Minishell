/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_data_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:15:15 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/13 14:17:33 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_data_redir(int *name, char *data)
{
	if (ft_strnstr(data, "<<") == 0)
		*name = HERE_DOC;
	else if (ft_strnstr(data, "<") == 0)
		*name = REDIR_IN;
	else if (ft_strnstr(data, ">>") == 0)
		*name = DREDIR_OUT;
	else if (ft_strnstr(data, ">") == 0)
		*name = REDIR_OUT;
	else
		return (1);
	return (0);
}

void	check_pos_one(t_cmd *comm, char *data, int pos)
{
	int	i;

	i = 0;
	if (comm->dt[0].name == COMMAND && pos == 1)
	{
		if (find_data_redir(&comm->dt[1].name, data) == 1)
			comm->dt[1].name = WORD;
	}
	else if (comm->dt[0].name != COMMAND && pos == 1)
	{
		if (comm->dt[0].name == HERE_DOC)
			comm->dt[pos].name = DELIMITER;
		else
			comm->dt[pos].name = DOC;
	}
}
