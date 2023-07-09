/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_error_one_arg.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:29:27 by maddou            #+#    #+#             */
/*   Updated: 2023/07/09 15:29:05 by mel-gand         ###   ########.fr       */
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
    if (lex->word[0][0] == '|')
    {
        free_double_array(lex->word);
        ft_printf("bash : syntax error\n");
        g_exit = 258;  
        return (-1);
    }
    while (lex->word[i])
    {
        if (ft_strcmp(lex->word[i], "|<") == 0 || ft_strnstr(lex->word[i], "|>") == 0 
            || ft_strnstr(lex->word[i], "<|") == 0 || ft_strnstr(lex->word[i], "><") == 0 
            || ft_strnstr(lex->word[i], ">>|") == 0 || ft_strnstr(lex->word[i], "<<|") == 0
            || ft_strnstr(lex->word[i], ">>>") == 0 || ft_strnstr(lex->word[i], "<>") == 0 
            || ft_strnstr(lex->word[i], "<<<") == 0 || ft_strnstr(lex->word[i], "||") == 0)
        {
            free_double_array(lex->word);
            ft_printf("bash : syntax error \n");   
            g_exit = 258; 
            return (-1);
        }
        i++;
    }
    return (0);  
}


