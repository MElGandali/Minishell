/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:34:17 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/14 13:13:40 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_valid(char *data, int i)
{
	if ((data[i + 1] == '_' || ft_isalnum(data[i + 1]) == 1 || data[i
				+ 1] == '\'' || data[i + 1] == '\"'))
		return (1);
	return (0);
}

int	check_quote(char *data, int i)
{
	char	c;

	if (data[i] == '\'' || data[i] == '\"')
	{
		c = data[i];
		while (data[i] != '\0' && data[i] == c)
			i++;
		if (data[i] == '\0')
			return (0);
	}
	return (1);
}

char	*ft_copier(char add, char *new_data)
{
	int		nb;
	int		i;
	char	*new;

	nb = 0;
	i = 0;
	if (new_data != NULL)
		nb = ft_strlen(new_data);
	new = malloc(sizeof(char) * (nb + 2));
	if (!new)
		return (0);
	if (new_data != NULL)
	{
		while (new_data[i] != '\0')
		{
			new[i] = new_data[i];
			i++;
		}
	}
	new[i++] = add;
	new[i] = '\0';
	free(new_data);
	return (new);
}

char	*copy_quote(char *data, int *i, char *new_data)
{
	new_data = ft_copier('\'', new_data);
	(*i)++;
	while (data[*i] != '\'')
	{
		new_data = ft_copier(data[*i], new_data);
		(*i)++;
	}
	new_data = ft_copier('\'', new_data);
	return (new_data);
}

void	handle_data(t_parser *parser)
{
	int	i;

	i = 0;
	while (i < parser->lex->pipe_nb)
	{
		parser->comm[i].dt = malloc(sizeof(t_data) * parser->comm[i].dt_nb);
		fill_data(parser->comm[i]);
		find_dollar(parser, &parser->comm[i]);
		handal_wildcard(parser, &parser->comm[i]);
		i++;
	}
}
