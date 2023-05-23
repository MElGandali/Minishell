/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_error_one_arg.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:29:27 by maddou            #+#    #+#             */
/*   Updated: 2023/05/23 19:57:00 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int quotes_error(t_lexer *lex)
{
    if (check_unclosed_quotes(lex->line) == -1)
        return (-1);
    return (0);   
}

int redir_pipe_error_one_arg(t_lexer *lex)
{
    int i;
    
    i = 0;
    while (lex->word[i])
    {
        if (ft_strnstr(lex->word[i], "|<") == 0 || ft_strnstr(lex->word[i], "|>") == 0 
            || ft_strnstr(lex->word[i], "<|") == 0 || ft_strnstr(lex->word[i], "><") == 0 
            || ft_strnstr(lex->word[i], ">>|") == 0 || ft_strnstr(lex->word[i], "<<|") == 0
            || ft_strnstr(lex->word[i], ">>>") == 0 || ft_strnstr(lex->word[i], "<>") == 0 
            || ft_strnstr(lex->word[i], "<<<") == 0 || ft_strnstr(lex->word[i], "||") == 0)
        {
            printf("bash : syntax error near unexpected token\n");    
            return (-1);
        }
        i++;
    }
    return (0);  
}


