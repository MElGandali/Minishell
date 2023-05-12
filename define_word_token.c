/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_word_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:34:17 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/12 21:25:26 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void define_word_token(t_lexer *lex)
{
    int i;

    i = 0;
    lex->enumerate = (char **) malloc(sizeof (char *) * (lex->word_nb + 1));
    if (!lex->enumerate)
        return ;

    while (lex->word[i])
    {
        if (ft_strcmp(lex->word[i], "|") == 0)
            lex->enumerate[i++] = "PIPE";
        else if (ft_strcmp(lex->word[i], ">") == 0)
            lex->enumerate[i++] = "REDIR_OUT";
        else if (ft_strcmp(lex->word[i], "<") == 0)
            lex->enumerate[i++] = "REDIR_IN";
        else if (ft_strcmp(lex->word[i], ">>") == 0)
            lex->enumerate[i++] = "DREDIR_OUT";
        else if (ft_strcmp(lex->word[i], "<<") == 0)
            lex->enumerate[i++] = "HERE_DOC";
        else
            lex->enumerate[i++] = "WORD";
    }
    lex->enumerate[i] = NULL;
}