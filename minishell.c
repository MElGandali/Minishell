/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:33:42 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/19 12:58:34 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int main()
{
    t_lexer lex;
    while (1)
    {
        lex.line = readline("bash$ ");
        add_history(lex.line);
        tokenizer(&lex);
    }
    return (0); 
}
