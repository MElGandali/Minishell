/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_newdata_beffor_after_check_ambigious.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 23:20:20 by maddou            #+#    #+#             */
/*   Updated: 2023/07/14 23:41:37 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	new_data(char **check_redirect, t_red *red)
{
	int	i;

	i = 0;
	while (check_redirect[0][i] != '\0')
	{
		if (ft_isprint(check_redirect[0][i]) == 1
			&& check_redirect[0][i] != '\"' && check_redirect[0][i] != '\''
			&& check_redirect[0][i] != ' ' &&
			check_redirect[0][i] != '\t')
		{
			red->copy_data = expand_name_file(red, check_redirect);
			free(red->data);
			red->data = ft_strdup(red->copy_data);
			free_double_array(check_redirect);
			return (0);
		}
		i++;
	}
	free_double_array(check_redirect);
	return (1);
}

void	new_data_after_check_am(char **check_redirect, t_red *red)
{
	red->copy_data = expand_name_file(red, check_redirect);
	free(red->data);
	if (red->copy_data != NULL)
		red->data = ft_strdup(red->copy_data);
	else
		red->data = NULL;
	free_double_array(check_redirect);
}

int	check_nb_redirect(int check, t_red *red, char **check_redirect)
{
	if (check == 0)
		return (1);
	else if (check > 1)
	{
		if (check_multi_arg(check_redirect) == 1)
		{
			free_double_array(check_redirect);
			return (1);
		}
	}
	else if (check == 1)
	{
		if (new_data(check_redirect, red) == 0)
			return (0);
		return (1);
	}
	return (0);
}
