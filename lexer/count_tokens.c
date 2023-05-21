/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:51:15 by maddou            #+#    #+#             */
/*   Updated: 2023/05/21 17:13:59 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_token(t_lexer *lex, int i)
{
	if (ft_strnstr(lex->word[i], "|") == 0 ||ft_strnstr(lex->word[i], "<<") == 0
		|| ft_strnstr(lex->word[i], ">>") == 0 || ft_strnstr(lex->word[i], "<") == 0
		|| ft_strnstr(lex->word[i], ">") == 0 || ft_strnstr(lex->word[i], ">|") == 0   
		|| ft_strnstr(lex->word[i], "|>") == 0 || ft_strnstr(lex->word[i], "|<") == 0)
			return (0);
	return (1);
}

void word_number (t_lexer *lex, int i, int j)
{
    while (lex->word[i][j] != '\0')
    {
        if (!(lex->word[i][j] == '>' || lex->word[i][j] == '<' 
		    || lex->word[i][j] == '|'))
	    {
	        while(!(lex->word[i][j] == '>' || lex->word[i][j] == '<' 
		        || lex->word[i][j] == '|') && lex->word[i][j] != '\0')
		    {
			    if (lex->word[i][j] == '\'' || lex->word[i][j] == '\"')
				    j = skip_quote(lex->word[i], j);
			    j++;
		    }
		    lex->curr_wnb++;
	    }
	    if ((lex->word[i][j] == '>' || lex->word[i][j] == '<' 
            || lex->word[i][j] == '|') && lex->word[i][j] != '\0')
	    {
		    while((lex->word[i][j] == '>' || lex->word[i][j] == '<' 
			    || lex->word[i][j] == '|') && lex->word[i][j] != '\0')
				    j++;
				lex->curr_wnb++;
		}
    }
}

void count_tokens (t_lexer *lex)
{
	int i;
	int j;

	i = 0;
	lex->curr_wnb = 0;
	while(lex->word[i])
	{
		if (check_token(lex, i) == 0)
		{
			j = 0;
            word_number (lex, i, j);
		}
		else
			lex->curr_wnb++;
		i++;
	}
}