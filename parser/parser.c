/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:36:07 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/11 12:51:01 by mel-gand         ###   ########.fr       */
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
    {
        free_double_array(lex->token);
        return (-1);
    }
    return (0);
}

int    parser(t_lexer *lex)
{
    t_parser parser;
    if (alloc_struct_cmd(lex , &parser) == -1)
        return (-1);
    fill_command (&parser);
    handle_data (&parser);
    fill_newcmd_red(&parser);
    executor(&parser);
    return (0);
}