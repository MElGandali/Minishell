/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:09:01 by maddou            #+#    #+#             */
/*   Updated: 2023/07/09 15:29:05 by mel-gand         ###   ########.fr       */
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
    lex->word = ft_split(lex->line, '\n' , &lex->curr_wnb);
    // last_wlen = ft_strlen(lex->word[lex->curr_wnb - 1]) - 1;
    // if (lex->word[0][0] == '|' || lex->word[lex->curr_wnb - 1][last_wlen] == '|')
    // {
    //     free (lex->line);
    //     free_double_array(lex->word);
    //     ft_printf("bash : syntax error near unexpected token1\n");
    //     return (-1);
    // }
    free (lex->line);
    return (0);
}
