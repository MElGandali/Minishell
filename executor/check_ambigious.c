/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambigious.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 23:13:57 by maddou            #+#    #+#             */
/*   Updated: 2023/07/14 23:41:33 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*fill_check_name(char **redirect, char *check_name, int i, int j)
{
	while (redirect[i][j] != '\0')
	{
		if (redirect[i][j] == '\'' || redirect[i][j] == '\"')
			check_name = if_quote_fill(redirect[i], &j, check_name);
		else
			check_name = ft_copier(redirect[i][j], check_name);
		j++;
	}
	return (check_name);
}

int	check_multi_arg(char **redirect)
{
	int		i;
	int		j;
	char	*check_name;
	int		check_null;
	int		check_char;

	i = 0;
	check_null = 0;
	check_char = 0;
	while (redirect[i] != NULL)
	{
		j = 0;
		check_name = NULL;
		check_name = fill_check_name(redirect, check_name, i, j);
		if (check_name != NULL)
			check_char++;
		free(check_name);
		i++;
	}
	if (check_char == 0 || check_char > 1)
		return (1);
	return (0);
}

int	check_multi(char **check_redirect)
{
	if (check_multi_arg(check_redirect) == 1)
	{
		free_double_array(check_redirect);
		return (1);
	}
	return (0);
}

int	check_empty(char *copy_data)
{
	int	i;

	i = 0;
	if (copy_data[0] == '\"' || copy_data[0] == '\'')
	{
		while (copy_data[i] != '\0' && copy_data[0] == copy_data[i])
			i++;
	}
	if (copy_data[i] == '\0')
		return (1);
	return (0);
}

int	check_ambiguous(t_red *red)
{
	int		i;
	char	**check_redirect;
	int		check;

	i = 0;
	if (red->copy_data == NULL)
		return (1);
	if (check_empty(red->copy_data) == 1)
		return (0);
	red->copy_data = split_data(red->copy_data);
	check_redirect = ft_split(red->copy_data, '\n', &check);
	if (check == 0)
		return (1);
	else if (check > 1 && check_multi(check_redirect) == 1)
		return (1);
	else if (check == 1)
	{
		if (new_data(check_redirect, red) == 0)
			return (0);
		return (1);
	}
	new_data_after_check_am(check_redirect, red);
	return (0);
}
