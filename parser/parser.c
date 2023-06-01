/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:36:07 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/01 16:57:43 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int alloc_struct_cmd(t_lexer *lex, t_parser *parser)
{   
    int i;
    
    parser->lex = lex;
    lex->pipe_nb = 1; 
    i = 0;
    while (lex->token[i])
    {
        if (ft_strnstr(lex->token[i], "|") == 0)
        {
            if (ft_strlen(lex->token[i]) <= 1)
                lex->pipe_nb++;
        }
        i++;
    }
    parser->comm = malloc (sizeof(t_cmd) * lex->pipe_nb);
    if (!parser->comm)
        return (-1);
    return (0);
}

int    parser(t_lexer *lex)
{
    t_parser parser;
    if (alloc_struct_cmd(lex , &parser) == -1)
        return (-1);
    fill_command (&parser);
    handle_data (&parser);
    // exit (0);
    return (0);
}