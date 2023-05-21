/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:38:20 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/21 20:00:52 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int tokenizer(t_lexer *lex)
{
    if (lex->line[0] == '\0')
    {
       free(lex->line);
       return (-1);
    }
    if (quotes_error(lex) == -1)
        return (-1);
    if (split_token(lex) == -1)
        return (-1);
    // if (pipe_error(lex) == -1)
    //     return (-1);
    return (0);
}