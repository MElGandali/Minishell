/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:33:42 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/23 18:51:28 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
#include "libf/libft.h"

int g_exit;

void all_work(t_lexer *lex)
{
    if (tokenizer(lex) == -1)
        return;
    if (parser(lex) == -1)
        return;
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    (void)env;
    t_lexer lex;
    // int g_exit;

    // g_exit = 0;
    lex.env = NULL;
    lex.exp= NULL;
    creating_new_env(&lex, env);
    while (1)
    {
        lex.line = readline("bash$ ");
        if (!lex.line)
            exit(0);
        add_history(lex.line);
        all_work(&lex);
    }
    return (0);
}
