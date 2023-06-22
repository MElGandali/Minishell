/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_error_one_arg.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:29:27 by maddou            #+#    #+#             */
/*   Updated: 2023/06/19 19:51:48 by maddou           ###   ########.fr       */
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
        printf("bash : syntax error\n");    
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
            printf("bash : syntax error \n");    
            return (-1);
        }
        i++;
    }
    return (0);  
}


