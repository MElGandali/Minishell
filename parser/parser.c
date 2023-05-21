/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:36:07 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/21 21:14:24 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void   pipe_number(char **str, t_lexer *lex)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_strnstr(str[i], "|") == 0)
            lex->pipe_nb++;
        i++;
    }
}

int alloc_struct_cmd(t_lexer *lex, t_parser *parser)
{   
    lex->pipe_nb = 1;
    if (lex->old_wnb < lex->curr_wnb) 
        pipe_number(lex->token, lex);  
    else 
        pipe_number(lex->word, lex);
    parser->cmd = (t_cmd *)malloc (sizeof(t_cmd *) * lex->pipe_nb);
    if (!parser)
        return (-1);
    return (0);
}

int    parser(t_lexer *lex)
{
    (void)lex;
    
    t_parser parser;
    if (alloc_struct_cmd(lex , &parser) == -1)
        return (-1);
    return (0);    
}