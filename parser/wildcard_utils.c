/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:22:41 by maddou            #+#    #+#             */
/*   Updated: 2023/07/14 00:22:48 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_calcule_etoile(char *data, int *i)
{
	int	j;

	j = 0;
	while (data[j] != '\0')
	{
		if (data[j] == '\'' || data[j] == '\"')
			j = skip_quote(data, j);
		if (data[j] == '*' && data[j + 1] != '*')
			(*i)++;
		j++;
	}
}

int	check_position_etoile(char *data, char c)
{
	if (c == 'o')
	{
		if (data[0] == '*')
			return (1);
		else if (data[ft_strlen(data)])
			return (2);
	}
	else
	{
		if (data[0] != '*' && data[ft_strlen(data) - 1] != '*')
			return (1);
		else if (data[0] != '*' && data[ft_strlen(data) - 1] == '*')
			return (2);
		else if (data[0] == '*' && data[ft_strlen(data) - 1] != '*')
			return (3);
		else if (data[0] == '*' && data[ft_strlen(data) - 1] == '*')
			return (4);
	}
	return (0);
}

int	check_valid_first(char *entry_name, char *patern)
{
	char	*patern_entry;

	patern_entry = ft_substr(entry_name, 0, ft_strlen(patern));
	if (!patern_entry)
		exit(1);
	if (patern_entry[0] != '.' && ft_strcmp(patern_entry, patern) == 0)
	{
		free(patern_entry);
		return (1);
	}
	free(patern_entry);
	return (0);
}

int	check_valid_last(char *entry_name, char *patern)
{
	char	*patern_entry;

	patern_entry = ft_substr(entry_name, ft_strlen(entry_name)
			- ft_strlen(patern), ft_strlen(entry_name));
	if (!patern_entry)
		exit(1);
	if (entry_name[0] != '.' && ft_strcmp(patern_entry, patern) == 0)
	{
		free(patern_entry);
		return (1);
	}
	free(patern_entry);
	return (0);
}

int	lenght_patern(char **patern)
{
	int	i;

	i = 0;
	while (patern[i] != NULL)
		i++;
	return (i);
}
