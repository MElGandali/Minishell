/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_error_mult_arg.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:48:10 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/19 19:50:51 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_syntax_error (t_lexer *lex, int i)
{
    if ((ft_strnstr(lex->token[i], "|") == 0 || 
        ft_strnstr(lex->token[i], ">") == 0
        || ft_strnstr(lex->token[i], "<") == 0) &&
        (ft_strnstr(lex->token[i + 1], "|")  == 0
        || ft_strnstr(lex->token[i + 1], ">") == 0
        || (ft_strnstr(lex->token[i + 1], "<") == 0 && ft_strlen(lex->token[i + 1]) == 1)))
    {
        free_double_array(lex->token);
        printf("bash : syntax error \n");
        return (-1);
    }
    return (0);
}

int redir_pipe_error_mult_arg(t_lexer *lex)
{  
    int i;

    i = 0;
    while (lex->token[i])
    {
        if (check_syntax_error(lex, i) == -1)
            return -1;
         if (ft_strnstr(lex->token[0], "|")  == 0 
            || ft_strnstr(lex->token[lex->curr_wnb - 1], "|") == 0
            || ft_strnstr(lex->token[lex->curr_wnb - 1], "<") == 0 
            || ft_strnstr(lex->token[lex->curr_wnb - 1], ">") == 0 )
        {
            free_double_array(lex->token);
            printf("bash : syntax error \n"); 
            return (-1);
        }
        i++;
    }
    return (0);
}