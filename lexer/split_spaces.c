/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:09:01 by maddou            #+#    #+#             */
/*   Updated: 2023/07/12 15:45:42 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_quote(char *line, int i)
{
	if (line[i] == '\"')
	{
		i++;
		while (line[i] != '\"')
			i++;
	}
	else if (line[i] == '\'')
	{
		i++;
		while (line[i] != '\'')
			i++;
	}
	return (i);
}

int	split_spaces(t_lexer *lex)
{
	int	i;

	i = 0;
	while (lex->line[i])
	{
		if (lex->line[i] == '\"' || lex->line[i] == '\'')
			i = skip_quote(lex->line, i);
		else if (lex->line[i] == ' ' || lex->line[i] == '\t'
			|| lex->line[i] == '\n')
			lex->line[i] = '\n';
		i++;
	}
	lex->word = ft_split(lex->line, '\n', &lex->curr_wnb);
	free(lex->line);
	return (0);
}
