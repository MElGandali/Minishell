/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:33:42 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/23 21:12:17 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void all_work(t_lexer *lex)
{ 
    if (tokenizer(lex) == -1)
        return;
    if (parser(lex) == -1)
        return;
 }

int main()
{
    t_lexer lex;
    while (1)
    {
        lex.line = readline("bash$ ");
        add_history(lex.line);
        all_work(&lex);
    }
    return (0); 
}
