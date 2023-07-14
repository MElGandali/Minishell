/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dollar_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:41:21 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/13 18:14:27 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_dollar_expand(char *data, char c, int j)
{
	++j;
	while (data[j] != c)
	{
		if (data[j] == '$')
		{
			if (c == '\"')
			{
				if (check_valid(data, j) == 1)
					return (1);
			}
		}
		j++;
	}
	return (0);
}

int	check_ex_dollar_utils(char *data, int *i, int j)
{
	if (data[*i] == '\'')
	{
		(*i)++;
		quote(data, i);
		if (check_if_dollar_expand(data, data[j], j) == 1)
			return (1);
	}
	else if (data[*i] == '\"')
	{
		(*i)++;
		dquote(data, i);
		if (check_if_dollar_expand(data, data[j], j) == 1)
			return (1);
	}
	else if (data[*i] == '$')
	{
		if (check_valid(data, *i) == 1)
			return (1);
	}
	return (0);
}

int	check_ex_dollar(char *data)
{
	int	i;
	int	j;

	i = 0;
	while (data[i] != '\0')
	{
		j = i;
		if (check_ex_dollar_utils(data, &i, j) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_expand_delimiter(char *delimiter)
{
	int	i;

	i = 0;
	while (delimiter[i] != '\0')
	{
		if (delimiter[i] == '\'' || delimiter[i] == '\"')
			return (0);
		i++;
	}
	return (1);
}

void	check_dollar(t_parser *parser, char *dquote, char **new_data)
{
	int	i;

	i = 0;
	while (dquote[i] != '\0')
	{
		if (dquote[i] == '$' && dquote[i + 1] != '?')
		{
			if (dquote[i + 1] == ' ')
				*new_data = ft_copier(dquote[i], *new_data);
			else if (dquote[i + 1] == '_' || ft_isalnum(dquote[i + 1]) == 1)
				expand_data(parser->lex->env, dquote, &i, new_data);
			else if (dquote[i + 1] != '\"' && !(dquote[i] == '_'
					|| ft_isalnum(dquote[i]) == 1))
				i++;
			else
				*new_data = ft_copier(dquote[i], *new_data);
		}
		else
			*new_data = ft_copier(dquote[i], *new_data);
		i++;
	}
}
