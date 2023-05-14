/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:58:21 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/14 17:46:54 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_end_utils(t_lexer *lex)
{
    while (lex->line[lex->i])
    {
        while (!((lex->line[lex->i] >= 9 && lex->line[lex->i] <= 13) || lex->line[lex->i] == 32) && lex->line[lex->i])
        {
            if (lex->line[lex->i] == 34 || lex->line[lex->i] == 39)
                lex->i = split_quotes(lex->line, lex->i);
            if (((lex->line[lex->i + 1] >= 9 && lex->line[lex->i + 1] <= 13) || lex->line[lex->i + 1] == 32) 
                || lex->line[lex->i + 1] == '\0')
                break;
            lex->i++;
        }
        if ((lex->line[lex->i] >= 9 && lex->line[lex->i] <= 13) || lex->line[lex->i] == 32)
            break;
        lex->i++;    
    }
    lex->i--;
    return (lex->i);
}