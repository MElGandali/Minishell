/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:42:22 by maddou            #+#    #+#             */
/*   Updated: 2023/05/15 23:36:42 by maddou           ###   ########.fr       */
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
    if (ft_strnstr(lex->word[i], "|") == 0 ||ft_strnstr(lex->word[i], "<<") == 0
        || ft_strnstr(lex->word[i], ">>") == 0 || ft_strnstr(lex->word[i], "<") == 0
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
int    cut_word(t_lexer *lex, int i, int j)
{
   if (lex->word[i][j] == '|' || lex->word[i][j] == '>' || lex->word[i][j] == '<')
   {
        while((lex->word[i][j] == '|' || lex->word[i][j] == '>' || lex->word[i][j] == '<') && lex->word[i][j] != '\0')
            j++;
        return (j - 1);
   }
   if (lex->word[i][j] != '|' || lex->word[i][j] != '>' || lex->word[i][j] != '<')
   {
        while (lex->word[i][j] != '|' || lex->word[i][j] != '>' || lex->word[i][j] != '<' 
            || lex->word[i][j])
        {
            if (lex->word[i][j] == '\"' || lex->word[i][j] == '\'')
                j = skip_quote(lex->word[i], j);
            j++;
        }
        return (j - 1);
   }
   return (0);
}
        // lex->start = j;
        
            // while (lex->word[i][j] != '|' || lex->word[i][j] != '>' || lex->word[i][j] != '<' 
            // || lex->word[i][j])
            // {
            //     if (lex->word[i][j] == '\"' || lex->word[i][j] == '\'')
            //         j = skip_quote(lex->word[i], j);
            //     j++;
            // }
        // }
        // while ()
        //     j++;
        // if (lex->word[i][j] == '|' || lex->word[i][j] == '>' || lex->word[i][j] == '<')
        // {
            
        // }
            
    // }
// }
int split_pipe_redir(t_lexer *lex)
{
    int i;
    int j;

    i = 0;
    j = 0;
    lex->copie_wnb = lex->word_nb;
    count_tokens (lex);
    
    if (lex->word_nb > lex->copie_wnb)
    {
        lex->token = (char **)malloc(sizeof(char *) * (lex->word_nb + 1));
        if (!lex->token)
            return (0);
        while (lex->word[i] != NULL)
        {
            if (ft_strnstr(lex->word[i], ">") == 0 || ft_strnstr(lex->word[i], "<") == 0 
                || ft_strnstr(lex->word[i], "|") == 0)
            {
                while(lex->word[i][j] != '\0')
                {
                    lex->start = j;
                    if (lex->word[i][j] == '|' || lex->word[i][j] == '>' || lex->word[i][j] == '<')
                        lex->end = cut_word(lex, i, j); 
                    if (lex->word[i][j] != '|' || lex->word[i][j] != '>' || lex->word[i][j] != '<')
                        lex->end = cut_word(lex, i, j);
                    // if(lex->word[i][j] =)
                }
                // cut_word(lex, i);   
            }
            else
                lex->token[j++] = ft_substr(lex->word[i], 0, ft_strlen(lex->word[i]));
            i++;    
        }
    }  
    return (1);
}

