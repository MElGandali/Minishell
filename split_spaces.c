/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:09:01 by maddou            #+#    #+#             */
/*   Updated: 2023/05/15 15:44:42 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libf/libft.h"
#include "minishell.h"

int skip_quote(char *line, int i)
{
    if (line[i] == '\"'/*34*/)
    {
        i++;
        while (line[i] != '\"'/*34*/)
            i++;
    }
    else if (line[i] == '\''/*39*/)
    {
        i++;
        while (line[i] != '\''/*39*/)
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
        if (line[i] == '\"'/*34*/ || line[i] == '\''/*39*/)
        {
            i = skip_quote(line, i);
            if (line[i + 1] == '\0')
                word_nb++;
        }
        else if (line[i] == ' ' && line[i + 1] != ' ')
            word_nb++;
        i++;
        
    }
    return (word_nb);   
}

int split_quotes(char *line, int i)
{
    i = skip_quote(line, i);
    if (((line[i + 1] >= 9 && line[i + 1] <= 13) || line[i + 1] == 32))
        return (i);
    else
    {
        while (line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == 32))
            i++;
    }
    return (i);
}

void find_end(t_lexer *lex)
{
    if (lex->line[lex->i] == '\"'/*34*/ || lex->line[lex->i] == '\''/*39*/)
    {
        lex->i = split_quotes(lex->line, lex->i);
        lex->end = lex->i;
    }
    if (lex->line[lex->i + 1] != ' ' || lex->line[lex->i + 1])
    {
        if (lex->line[lex->i] == '\"'/*34*/ || lex->line[lex->i] == '\''/*39*/)
            lex->i++;
        lex->end = find_end_utils(lex);
    }
}

int split_spaces(t_lexer *lex)
{
    lex->i = 0;
    lex->j = 0;
    if ((lex->word_nb = word_count(lex->line)) == 0)
        return 0;
    lex->word = (char **) malloc(sizeof(char *) * (lex->word_nb + 2));
    if (!lex->word)
        return 0;
    while(lex->line[lex->i] != '\0')
    {
        while(((lex->line[lex->i] >= 9 && lex->line[lex->i] <= 13) || 
                lex->line[lex->i] == 32))
            lex->i++;
        lex->start = lex->i;
        find_end(lex);
        lex->word[lex->j++] = ft_substr(lex->line, lex->start, lex->end - lex->start);
        lex->i++;
    }
    return (1);
}