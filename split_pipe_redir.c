/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:42:22 by maddou            #+#    #+#             */
/*   Updated: 2023/05/13 17:56:49 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_position(int *end, int *start, char *word)
{
    while(word[*end] != '\0')
    {
        if (word[*end] == '>' )
        (*end)++;
    }
}

char **split_pipe_redir(t_lexer *lex)
{
    int i;
    int j;

    i = 0;
    j  = 0;
    while (lex->word[i] != NULL)
    {
        check_position (&i, &j, lex->word[i]);
        i++;
    }
    // lex->token_nb = count_token(lex->word);
    return (lex->word);
}

