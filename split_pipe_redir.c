/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:42:22 by maddou            #+#    #+#             */
/*   Updated: 2023/05/13 21:33:13 by maddou           ###   ########.fr       */
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
    if (ft_strnstr(lex->word[i], "<<") == 0 || ft_strnstr(lex->word[i], ">>") == 0 
        || ft_strnstr(lex->word[i], "<<<") == 0 || ft_strnstr(lex->word[i], "<") == 0 
        || ft_strnstr(lex->word[i], ">") == 0 || ft_strnstr(lex->word[i], ">|") == 0   
        || ft_strnstr(lex->word[i], "|>") == 0 || ft_strnstr(lex->word[i], "|<") == 0 )
        return (0);
    i++;
   }
   return (1);
}
void fill_node (t_lexer *lex, int i)
{
    int j;
    int c;

    j = 0;
    c = 0;
    while(lex->word[i][j] != '\0')
    {
        if (lex->word[i][j] == '\'' || lex->word[i][j] == '\"')
            j = skip_quote(lex->word[i], j);
        if (lex->word[i][j] == '|' || lex->word[i][j] == '>' || lex->word[i][j] == '<')
        {
            
        }
        j++;
    }
}
void first_node(t_lexer *lex)
{
    lex->head = (t_token *)malloc (sizeof(t_token));
    lex->tmp = lex->head; 
    if (check_token(lex) == 1)
    {
        lex->tmp->word = lex->word[0];
        lex->tmp->free = 0;
        lex->tmp->next = NULL;
    }
    else 
    {
        
        fill_node(lex);
    }
}

char **split_pipe_redir(t_lexer *lex)
{
    int i;
    int j;
    t_token token;

    i = 0;
    j = 0;
    first_node(lex);
    while (lex->word[++i] != NULL)
    {
        if (check_token(lex) == 1)
            
        i++;
    }
    return (lex->word);
}

