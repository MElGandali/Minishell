/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:21:20 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/14 22:52:35 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_dollar(t_parser *parser, char *data, char *new_data, int *j)
{
	if (data[*j] == '$' && data[*j + 1] != '\0' && data[*j + 1] != '?')
	{
		if (data[*j] == ' ')
			new_data = ft_copier(data[*j + 1], new_data);
		else if (data[*j + 1] == '_' || ft_isalnum(data[*j + 1]) == 1)
			expand_data(parser->lex->env, data, j, &new_data);
		else if (!(data[*j + 1] == '_' || ft_isalnum(data[*j + 1]) == 1)
			&& data[*j + 1] != '\0' && data[*j + 1] != '\'' && data[*j
				+ 1] != '\"')
			(*j)++;
		else if (data[*j + 1] != '\'' && data[*j + 1] != '\"')
			new_data = ft_copier(data[*j], new_data);
	}
	else if (data[*j] != '\'' && data[*j] != '\"')
		new_data = ft_copier(data[*j], new_data);
	return (new_data);
}

char	*check_dquote_before_expand(char *data, char *dquote, int *j)
{
	dquote = ft_copier(data[*j], dquote);
	(*j)++;
	while (data[*j] != '\"')
		dquote = ft_copier(data[(*j)++], dquote);
	dquote = ft_copier(data[*j], dquote);
	return (dquote);
}

char	*find_dollar_utils(t_parser *parser, char *data, int j, char e)
{
	char	*new_data;
	char	*dquote;

	new_data = NULL;
	if (data == NULL)
		return (data);
	while (data[j] != '\0')
	{
		dquote = NULL;
		if (e == 'n' && data[j] == '\'')
			new_data = copy_quote(data, &j, new_data);
		if (e == 'e' && data[j] == '\'')
		{
			dquote = copy_quote(data, &j, new_data);
			check_dollar(parser, dquote, &new_data);
		}
		if (data[j] == '\"')
		{
			dquote = check_dquote_before_expand(data, dquote, &j);
			check_dollar(parser, dquote, &new_data);
		}
		else
			new_data = expand_dollar(parser, data, new_data, &j);
		free(dquote);
		j++;
	}
	return (new_data);
}

void	fill_newdata(t_cmd *cmd, int i, char *new_data)
{
	if (new_data == NULL)
	{
		cmd->dt[i].name = WALLO;
		free(cmd->dt[i].data);
		free(cmd->dt[i].copy_data);
		cmd->dt[i].data = NULL;
		cmd->dt[i].copy_data = NULL;
	}
	else
	{
		free(cmd->dt[i].data);
		free(cmd->dt[i].copy_data);
		cmd->dt[i].data = ft_strdup(new_data);
		cmd->dt[i].copy_data = ft_strdup(new_data);
	}
}

void	find_dollar(t_parser *parser, t_cmd *cmd)
{
	int		i;
	int		j;
	char	*new_data;

	i = 0;
	while (i < cmd->dt_nb)
	{
		j = 0;
		new_data = NULL;
		if (cmd->dt[i].name != 10 && cmd->dt[i].name != 4
			&& cmd->dt[i].name != 5 && cmd->dt[i].name != 6
			&& cmd->dt[i].name != 7)
		{
			new_data = find_dollar_utils(parser, cmd->dt[i].data, j, 'n');
			fill_newdata(cmd, i, new_data);
		}
		free(new_data);
		i++;
	}
}
