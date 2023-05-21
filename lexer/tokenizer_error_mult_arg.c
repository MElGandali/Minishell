/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_error_mult_arg.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:48:10 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/21 17:14:24 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_args(char **str)
{
    int i;

    i = 0;
     while (str[i])
        {
            if ((ft_strnstr(str[i], ">") == 0 || ft_strnstr(str[i], "<") == 0) &&
                (ft_strnstr(str[i + 1], "|")  == 0 || ft_strnstr(str[i + 1], ">") == 0 
                || ft_strnstr(str[i + 1], "<") == 0))
            {
                printf("bash : syntax error near unexpected token\n"); 
                return (-1);
            }
            if ((ft_strnstr(str[i], "|")  == 0 && ft_strnstr(str[i + 1], "|")  == 0) 
                || ft_strnstr(str[0], "|")  == 0)
            {
                printf("bash : syntax error near unexpected token\n"); 
                return (-1);
            }
            i++;
        }
        return (0);
}

int redir_pipe_error_mult_arg(t_lexer *lex)
{   
    if (lex->old_wnb < lex->curr_wnb)
    {
        if (check_args(lex->token) == -1)
            return (-1);
    }
    else 
    {
        if (check_args(lex->word) == -1)
            return (-1);
    }
    return (0);
}