/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:42:22 by maddou            #+#    #+#             */
/*   Updated: 2023/07/12 16:25:58 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_end_ifnot_redir(t_lexer *lex, int i, int j)
{
	while ((lex->word[i][j] != '|' && lex->word[i][j] != '>'
			&& lex->word[i][j] != '<') && lex->word[i][j + 1])
	{
		if (lex->word[i][j] == '\"' || lex->word[i][j] == '\'')
		{
			j = skip_quote(lex->word[i], j);
			if (((lex->word[i][j] == '\"' || lex->word[i][j] == '\'')
						&& lex->word[i][j + 1]) == '\0')
				break ;
		}
		if (lex->word[i][j + 1] == '|' || lex->word[i][j + 1] == '>'
			|| lex->word[i][j + 1] == '<')
			break ;
		j++;
	}
	return (j);
}

int	find_word(t_lexer *lex, int i, int j)
{
	if (lex->word[i][j] == '|' || lex->word[i][j] == '>'
		|| lex->word[i][j] == '<')
	{
		while ((lex->word[i][j + 1] == '|' || lex->word[i][j + 1] == '>'
				|| lex->word[i][j + 1] == '<') && lex->word[i][j + 1])
			j++;
		lex->end = j;
	}
	else if (lex->word[i][j] != '|' && lex->word[i][j] != '>'
			&& lex->word[i][j] != '<')
	{
		j = find_end_ifnot_redir(lex, i, j);
		lex->end = j;
	}
	return (j);
}

void	fill_token(t_lexer *lex, int i, int j, int *k)
{
	while (lex->word[i] != NULL)
	{
		j = 0;
		if (ft_strnstr(lex->word[i], ">") == 0 || ft_strnstr(lex->word[i],
				"<") == 0 || ft_strnstr(lex->word[i], "|") == 0)
		{
			while (lex->word[i][j] != '\0')
			{
				lex->start = j;
				j = find_word(lex, i, j);
				lex->token[(*k)++] = ft_substr(lex->word[i], lex->start,
						(lex->end - lex->start) + 1);
				j++;
			}
		}
		else
			lex->token[(*k)++] = ft_substr(lex->word[i], 0,
					ft_strlen(lex->word[i]));
		i++;
	}
}

int	split_pipe_redir(t_lexer *lex)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	count_tokens(lex);
	lex->token = (char **)malloc(sizeof(char *) * (lex->curr_wnb + 1));
	if (!lex->token)
		return (-1);
	fill_token(lex, i, j, &k);
	lex->token[k] = NULL;
	free_double_array(lex->word);
	return (1);
}
