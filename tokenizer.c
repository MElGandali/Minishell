/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:38:20 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/12 16:48:29 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int tokenizer(t_lexer *lex)
{
    if (tokenizer_error(lex->line) == -1)
        return (-1);
    split_token(lex);
    
    return (0);
}