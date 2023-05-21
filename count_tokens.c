/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:51:15 by maddou            #+#    #+#             */
/*   Updated: 2023/05/21 11:51:18 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		    lex->word_nb++;
	    }
	    if ((lex->word[i][j] == '>' || lex->word[i][j] == '<' 
            || lex->word[i][j] == '|') && lex->word[i][j] != '\0')
	    {
		    while((lex->word[i][j] == '>' || lex->word[i][j] == '<' 
			    || lex->word[i][j] == '|') && lex->word[i][j] != '\0')
				    j++;
				lex->word_nb++;
		}
    }
}

void count_tokens (t_lexer *lex)
{
	int i;
	int j;

	i = 0;
	lex->word_nb = 0;
	while(lex->word[i])
	{
		if (check_token(lex, i) == 0)
		{
			j = 0;
            word_number (lex, i, j);
			// while (lex->word[i][j])
			// {
			// 	if (!(lex->word[i][j] == '>' || lex->word[i][j] == '<' 
			// 	|| lex->word[i][j] == '|'))
			// 	{
			// 		while(!(lex->word[i][j] == '>' || lex->word[i][j] == '<' 
			// 			|| lex->word[i][j] == '|') && lex->word[i][j] != '\0')
			// 		{
			// 			if (lex->word[i][j] == '\'' || lex->word[i][j] == '\"')
			// 				j = skip_quote(lex->word[i], j);
			// 			j++;
			// 		}
			// 		lex->word_nb++;
			// 	}
			// 	if ((lex->word[i][j] == '>' || lex->word[i][j] == '<' 
            //         || lex->word[i][j] == '|') && lex->word[i][j] != '\0')
			// 	{
			// 		while((lex->word[i][j] == '>' || lex->word[i][j] == '<' 
			// 			|| lex->word[i][j] == '|') && lex->word[i][j] != '\0')
			// 			j++;
			// 		lex->word_nb++;
			// 	}
			// }
		}
		else
			lex->word_nb++;
		i++;
	}
}