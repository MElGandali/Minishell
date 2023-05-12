/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:09:01 by maddou            #+#    #+#             */
/*   Updated: 2023/05/12 12:04:00 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int skip_quote(char *line, int i)
{
    if (line[i] == 34)
    {
        i++;
        while (line[i] != 34)
            i++;
    }
    else if (line[i] == 39)
    {
        i++;
        while (line[i] != 39)
            i++;
    }
    return (i);
}

int word_count(char *line)
{
    int word_nb;
    int        i;

    word_nb = 0;
    i = 0;
    while(((line[i] >= 9 && line[i] <= 13) || line[i] == 32) && line[i] != '\0')
        i++;
    while(line[i] != '\0')
    {
        if (line[i] != ' ' && line[i + 1] == '\0')
            word_nb++;
        if (line[i] == ' ' && line[i + 1] != ' ')
            word_nb++;
        else if (line[i] == 34 || line[i] == 39)
        {
            i = skip_quote(line, i);
            if (line[i + 1] == '\0')
                word_nb++;
        }
        i++;
    }
    return (word_nb);   
}

char **split_spaces(t_lexer *lex)
{
    lex->i = 0;
    if ((lex->word_nb = word_count(lex->line)) == 0)
        return 0;
    printf("%d", lex->word_nb);
    lex->word = (char **) malloc((sizeof(char *) * lex->word_nb) + 1);
    if (!lex->word)
        return (0);
    while(lex->line[lex->i] != '\0')
    {
        while(((lex->line[lex->i] >= 9 && lex->line[lex->i] <= 13) || 
                lex->line[lex->i] == 32))
            lex->start = lex->i++;
        while(lex->line[lex->i] == ' ')
            lex->i++;
    }
    return (lex->word);
}