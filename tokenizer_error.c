/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:29:27 by maddou            #+#    #+#             */
/*   Updated: 2023/05/14 14:12:36 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int quotes_error(t_lexer *lex)
{
    if (check_unclosed_quotes(lex->line) == -1)
        return (-1);
    return (0);   
}

int redir_pipe_error(t_lexer *lex)
{
    int i;
    
    i = 0;
    while (lex->word[i])
    {
        if (ft_strnstr(lex->word[i], "<|") == 0 || ft_strnstr(lex->word[i], "><") == 0 
            || ft_strnstr(lex->word[i], ">>|") == 0 || ft_strnstr(lex->word[i], "<<|") == 0 
            || ft_strnstr(lex->word[i], ">>>") == 0 || ft_strnstr(lex->word[i], "<>") == 0   
            || ft_strnstr(lex->word[i], "<<>") == 0 || ft_strnstr(lex->word[i], ">><") == 0 
            || ft_strnstr(lex->word[i], "<<<|") == 0 || ft_strnstr(lex->word[i], "<<<>") == 0 
            || ft_strnstr(lex->word[i], "<<<<") == 0 || ft_strnstr(lex->word[i], "|||") == 0
            || ft_strnstr(lex->word[i], ">||") == 0)
        {
            //free word, readline
            printf("bash : syntax error near unexpected token\n");    
            return (-1);
        }
        i++;
    }
    return (0);  
}

int pipe_error(t_lexer *lex)
{
    int i;

    i = 0;
    while (lex->enumerate[i])
    {
        if (ft_strcmp(lex->enumerate[i], "PIPE") == 0)
        {
            if (ft_strcmp(lex->enumerate[i - 1], "WORD") != 0)
            {
                // free line free word free enumerate
                printf("bash : syntax error near unexpected token `|'\n");
                return (-1);
            }
        }
        i++;
    }
    return (0);
}
