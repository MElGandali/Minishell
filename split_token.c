/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:06:38 by maddou            #+#    #+#             */
/*   Updated: 2023/05/15 21:17:42 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int  split_token(t_lexer *lex)
{
    if(split_spaces(lex) == 0)   //  min min ndiro enter ghadi trad 0 oghadi yatra sgv 3lach darna had if
        return (-1); 
    // if (pipe_error(lex) == -1)
    //     return (-1);
    if (redir_pipe_error(lex) == -1)
        return(-1);
    split_pipe_redir(lex);
    // define_word_token(lex);   
    return (0);
}