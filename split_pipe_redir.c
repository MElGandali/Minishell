/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:42:22 by maddou            #+#    #+#             */
/*   Updated: 2023/05/15 15:32:48 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int check_token(t_lexer *lex)
{
   int i;
   int j;
    
   i = 0;
   j = 0; 
   while(lex->word[i] != NULL)
   {
    if (ft_strnstr(lex->word[i], "|") == 0 || ft_strnstr(lex->word[i], "<<") == 0 
        || ft_strnstr(lex->word[i], ">>") == 0 
        || ft_strnstr(lex->word[i], "<<<") == 0 || ft_strnstr(lex->word[i], "<") == 0
        || ft_strnstr(lex->word[i], ">") == 0 || ft_strnstr(lex->word[i], ">|") == 0   
        || ft_strnstr(lex->word[i], "|>") == 0 || ft_strnstr(lex->word[i], "|<") == 0)
        return (0);
    i++;
   }
   return (1);
}
void count_tokens (t_lexer *lex)
{
    int i;
    int j;

    i = 0;
    j = 0;

    while(lex->word[i])
    {
        if (check_token(lex) == 0)
        {
            j = 0;
            while (lex->word[i][j])
            {
                if (lex->word[i][j] == '\'' || lex->word[i][j] == '\"')
                    j = skip_quote(lex->word[i], j);
                if ((lex->word[i][j] == '>' || lex->word[i][j] == '<' || (lex->word[i][j] == '|' && lex->word[i][j + 1] != '|')))
                {
                    if (j != 0) // error in first index ila kan f lbadya kayzid hna wahad o3awdakin ltaht iziid wahad 
                        lex->word_nb += 1;
                    while ((lex->word[i][j] == '>' || lex->word[i][j] == '<' || lex->word[i][j] == '|') && lex->word[i][j])
                        j++;
                    if (!(lex->word[i][j] == '>' || lex->word[i][j] == '<' || lex->word[i][j] == '|') && lex->word[i][j])
                        lex->word_nb += 1;
                }
                if ((lex->word[i][j] == '|' && lex->word[i][j + 1] == '|'))
                    j++;
                j++;
            }
        }
        i++;
    }
}

char **split_pipe_redir(t_lexer *lex)
{
    int i;
    int j;

    i = 0;
    j = 0;
    count_tokens (lex); 
    return (0);
}

