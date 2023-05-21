/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:09:01 by maddou            #+#    #+#             */
/*   Updated: 2023/05/17 23:38:42 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

void split_spaces(t_lexer *lex)
{
    int i;

    i = 0;
    while (lex->line[i])
    {
        if (lex->line[i] == '\"' || lex->line[i] == '\'')
            i = skip_quote(lex->line, i);
        else if (lex->line[i] == ' ' || lex->line[i] == '\t' || lex->line[i] == '\n')
            lex->line[i] = '\n';
    i++;
    }
    lex->word = ft_split(lex->line, '\n' , &lex->word_nb);
    free (lex->line);
    // i = 0;   
    // while(lex->word[i] != NULL)
    //     printf("%s--\n", lex->word[i++]);
}
