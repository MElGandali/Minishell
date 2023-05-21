/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:09:01 by maddou            #+#    #+#             */
/*   Updated: 2023/05/21 18:25:51 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

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

int split_spaces(t_lexer *lex)
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
    if (lex->line[0] == '|' || lex->line[i - 1] == '|')
    {
        
        printf("bash : syntax error near unexpected token\n");
        free(lex->line);
        return (-1);
    }
    lex->word = ft_split(lex->line, '\n' , &lex->curr_wnb);
    free (lex->line);
    return (0);
}
