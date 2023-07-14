/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambigious_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 23:17:31 by maddou            #+#    #+#             */
/*   Updated: 2023/07/14 23:28:10 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*split_data(char *copy_data)
{
	int	i;

	i = 0;
	while (copy_data[i] != '\0')
	{
		if (copy_data[i] == '\"' || copy_data[i] == '\'')
			i = skip_quote(copy_data, i);
		else if (copy_data[i] == ' ' || copy_data[i] == '\t'
			|| copy_data[i] == '\n')
			copy_data[i] = '\n';
		i++;
	}
	return (copy_data);
}

char	*fill_new_name(char **check_redirect, int j, int i)
{
	char	*new_name;

	while (check_redirect[i] != NULL)
	{
		j = 0;
		new_name = NULL;
		while (check_redirect[i][j] != '\0')
		{
			if (check_redirect[i][j] == '\'' || check_redirect[i][j] == '\"')
				new_name = if_quote_fill(check_redirect[i], &j, new_name);
			else
				new_name = ft_copier(check_redirect[i][j], new_name);
			j++;
		}
		i++;
	}
	return (new_name);
}

char	*expand_name_file(t_red *red, char **check_redirect)
{
	int		i;
	int		j;
	char	*new_name;

	i = 0;
	free(red->copy_data);
	red->copy_data = NULL;
	new_name = fill_new_name(check_redirect, j, i);
	if (new_name != NULL)
		red->copy_data = ft_strdup(new_name);
	else
		red->copy_data = NULL;
	free(new_name);
	return (red->copy_data);
}

void	print_ambiguous_error(void)
{
	ft_printf("bash: ambiguous redirect\n");
	g_exit = 1;
}
