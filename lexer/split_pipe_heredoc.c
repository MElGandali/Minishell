/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:14:32 by maddou            #+#    #+#             */
/*   Updated: 2023/07/10 13:01:26 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int countntoken(char **token, int cur_wnb)
{
    int nb;
    int i;

    i = 0;
    nb = cur_wnb;
    while (token[i] != NULL)
    {
        if (ft_strcmp(token[i], "|<<") == 0)
            nb++;
        i++;
    }
    return (nb);
}

int split_pipe_heredoc(t_lexer *lex)
{
    int i;
    int j;
    char **new_token;
    int nb;
    
    
    nb = countntoken(lex->token, lex->curr_wnb);
    i = 0;
    j = 0;
    new_token = NULL;
    if (nb > lex->curr_wnb)
    {
        lex->curr_wnb = nb;
        new_token = malloc(sizeof(char *) * (nb + 1));
        if (!new_token)
            return -1;
        while (lex->token[i] != NULL)
        {
            if (ft_strcmp(lex->token[i], "|<<") == 0)
            {
                new_token[j++] = ft_strdup("|");
                new_token[j] = ft_strdup("<<");
            }
            else   
                new_token[j] = ft_strdup(lex->token[i]);
            j++;
            i++;
        }
        new_token[j] = NULL;
        free_double_array(lex->token);
        lex->token = new_token;
    }
    return (0);
}