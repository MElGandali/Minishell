/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:36:07 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/21 19:29:15 by mel-gand         ###   ########.fr       */
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

void alloc_struct_cmd(t_lexer *lex, t_parser *parser)
{   
    lex->pipe_nb = 1;
    if (lex->old_wnb < lex->curr_wnb) 
        pipe_number(lex->token, lex);  
    else 
        pipe_number(lex->word, lex);
    printf("pipe alloc%d\n", lex->pipe_nb);
    parser = (t_parser *)malloc (sizeof(t_parser *) *lex->pipe_nb + 1);
    
}

void    parser(t_lexer *lex)
{
    (void)lex;
    
    t_parser parser;
    alloc_struct_cmd(lex , &parser);     
}