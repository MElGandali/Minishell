/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:09:01 by maddou            #+#    #+#             */
/*   Updated: 2023/05/16 23:45:53 by mel-gand         ###   ########.fr       */
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

void split_spaces(t_lexer *lex)
{
    int i;

    i = 0;
    while (lex->line[i])
    {
        if (lex->line[i] == '\"' || lex->line[i] == '\'')
            i = skip_quote(lex->line, i);
        else if (lex->line[i] == ' ' && lex->line[i + 1] != ' ' && lex->line[i + 1] != '\0')
            lex->line[i] = '\n';
    i++;
    }
    lex->word = ft_split(lex->line, '\n');
    printf("%s", lex->word[0]);
    printf("%s", lex->word[1]);
    exit(0);
}
// int word_count(char *line)
// {
//     int word_nb;
//     int        i;

//     word_nb = 0;
//     i = 0;
//     while(((line[i] >= 9 && line[i] <= 13) || line[i] == 32) && line[i] != '\0')
//         i++;
//     while(line[i] != '\0')
//     {
//         if (line[i] != ' ' && line[i + 1] == '\0')
//             word_nb++;
//         if (line[i] == '\"'/*34*/ || line[i] == '\''/*39*/)
//         {
//             i = skip_quote(line, i);
//             if (line[i + 1] == '\0')
//                 word_nb++;
//         }
//         else if (line[i] == ' ' && line[i + 1] != ' ')
//             word_nb++;
//         i++;
        
//     }
//     return (word_nb);   
// }

// int split_quotes(char *line, int i)
// {
//     i = skip_quote(line, i);
//     if (((line[i + 1] >= 9 && line[i + 1] <= 13) || line[i + 1] == 32))
//         return (i);
//     else
//     {
//         while (line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == 32))
//             i++;
//     }
//     return (i);
// }

// void find_end(t_lexer *lex)
// {
//     if (lex->line[lex->i] == '\"'/*34*/ || lex->line[lex->i] == '\''/*39*/)
//     {
//         lex->i = split_quotes(lex->line, lex->i);
//         lex->end = lex->i;
//     }
//     if (lex->line[lex->i] != ' ' || lex->line[lex->i])
//     {
//         if (lex->line[lex->i] == '\"'/*34*/ || lex->line[lex->i] == '\''/*39*/)
//             lex->i++;
//         lex->end = find_end_utils(lex);
//     }
// //     if (((lex->line[lex->i] >= 9 && lex->line[lex->i] <= 13) || 
// //                 lex->line[lex->i] == 32))
// //     {
      
// //     }
// // }
// }

// int split_spaces(t_lexer *lex)
// {
//     lex->i = 0;
//     lex->j = 0;
//     if ((lex->word_nb = word_count(lex->line)) == 0)
//         return 0;
//     printf("nb word%d\n", lex->word_nb);
//     lex->word = (char **) malloc(sizeof(char *) * (lex->word_nb + 1));
//     if (!lex->word)
//         return 0;
//     while(lex->line[lex->i] != '\0')
//     {
//         while(((lex->line[lex->i] >= 9 && lex->line[lex->i] <= 13) || 
//             lex->line[lex->i] == 32) && lex->line[lex->i])
//         {
//             lex->i++;
//             printf("index %d\n", lex->i);
//         }
//             lex->start = lex->i;
//         find_end(lex);
//         printf("start : %d----end %d\n", lex->start, lex->end);
//         lex->word[lex->j++] = ft_substr(lex->line, lex->start, lex->end - lex->start);
//     printf("%s\n", lex->word[--lex->j]);
        
//         lex->i++;
//     }
//     lex->word[lex->j] = NULL;
//     return (1);
// }