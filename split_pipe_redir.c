/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:42:22 by maddou            #+#    #+#             */
/*   Updated: 2023/05/17 23:55:09 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int check_token(t_lexer *lex, int i)
{
    if (ft_strnstr(lex->word[i], "|") == 0 ||ft_strnstr(lex->word[i], "<<") == 0
        || ft_strnstr(lex->word[i], ">>") == 0 || ft_strnstr(lex->word[i], "<") == 0
        || ft_strnstr(lex->word[i], ">") == 0 || ft_strnstr(lex->word[i], ">|") == 0   
        || ft_strnstr(lex->word[i], "|>") == 0 || ft_strnstr(lex->word[i], "|<") == 0)
            return (0);
    return (1);
}

void count_tokens (t_lexer *lex)
{
    int i;
    int j;

    i = 0;
    while(lex->word[i])
    {
        if (check_token(lex, i) == 0)
        {
            j = 0;
            if ((lex->word[i][j] == '>' 
                || lex->word[i][j] == '<' || lex->word[i][j] == '|'))
            {
                while(lex->word[i][j] != '\0' && (lex->word[i][j] == '>' 
                    || lex->word[i][j] == '<' || lex->word[i][j] == '|'))
                    j++;
            }
            if (lex->word[i][j] != '\0')
            {
                j = 0;
                while (lex->word[i][j])
                {
                    if (lex->word[i][j] == '\'' || lex->word[i][j] == '\"')
                        j = skip_quote(lex->word[i], j);
                    else if (lex->word[i][j] == '>' || lex->word[i][j] == '<' || lex->word[i][j] == '|')
                    {
                        while((lex->word[i][j + 1] == '>' || lex->word[i][j + 1] == '<' 
                            || lex->word[i][j + 1] == '|') && lex->word[i][j + 1] != '\0')
                            j++;
                        if (j != 0 && (lex->word[i][j + 1] != '>' || lex->word[i][j + 1] != '<' 
                            || lex->word[i][j + 1] != '|') && lex->word[i][j + 1] != '\0')
                            lex->word_nb++;
                        lex->word_nb++;
                    }
                    j++;
                }
            }
        }
        i++;
    }
}

int    find_word(t_lexer *lex, int i, int j)
{
    if (lex->word[i][j] == '|' || lex->word[i][j] == '>' || lex->word[i][j] == '<')
    {
        while ((lex->word[i][j + 1] == '|' || lex->word[i][j + 1] == '>' 
        || lex->word[i][j + 1] == '<') && lex->word[i][j + 1]) // if we change the || to && we will find that it split every redirection seperately even if they're next to each other
            j++;
        lex->end = j;
    }
    else if (lex->word[i][j] != '|' || lex->word[i][j] != '>' || lex->word[i][j] != '<')
    {
        while ((lex->word[i][j + 1] != '|' && lex->word[i][j + 1] != '>' 
        && lex->word[i][j + 1] != '<') && lex->word[i][j + 1])
        {
            if (lex->word[i][j] == '\"' || lex->word[i][j] == '\'')
                j = skip_quote(lex->word[i], j) - 1; // j will increment after this condition so we need to substract 1 to even it
            j++;
        }
        lex->end = j;
    }
    return (j);
}

int split_pipe_redir(t_lexer *lex)
{
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    lex->copie_wnb = lex->word_nb;
    count_tokens(lex);
    if (lex->word_nb > lex->copie_wnb)
    {
        lex->token = (char **)malloc(sizeof(char *) * (lex->word_nb + 1));
        if (!lex->token)
            return (0);
        while (lex->word[i] != NULL)
        {
            if (ft_strnstr(lex->word[i], ">") == 0 || ft_strnstr(lex->word[i], "<") == 0 
                || ft_strnstr(lex->word[i], "|") == 0)
            {
                while(lex->word[i][j] != '\0')
                {
                    lex->start = j;
                    j = find_word(lex, i, j);
                    lex->token[k++] = ft_substr(lex->word[i], lex->start, lex->end - lex->start);
                    j++;
                }
            }
            else
                lex->token[k++] = ft_substr(lex->word[i], 0, ft_strlen(lex->word[i]));
            i++;
        }
        lex->token[k] = NULL;
    }
    i = 0;
    printf("%d\n", lex->word_nb);
    // if (lex->copie_wnb < lex->word_nb)
    // {
    //     while (lex->token[i])
    //     {
            
    //         printf("%s\n", lex->token[i]);
    //         i++;
    //     }
    // }
    // else   
    // {
    //     while(lex->word[i] != NULL)
    //         printf("%s==\n", lex->word[i++]);
    // }
    exit (0);
    return (1);
}

