/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:06:38 by maddou            #+#    #+#             */
/*   Updated: 2023/05/21 19:32:30 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int split_token(t_lexer *lex)
{
    if (split_spaces(lex) == - 1)
        return (-1);
    // if (lex->word[0] == NULL) //do we have to free the null
    // {
    //     free (lex->word[0]);
    //     return (-1);
    // }
    if (redir_pipe_error_one_arg(lex) == -1)
        return(-1); //free word
    if (split_pipe_redir(lex) == -1)
        return (-1); //free word, free token
    if (redir_pipe_error_mult_arg(lex) == -1)
        return (-1);
    // define_word_token(lex);   
    return (0);
}