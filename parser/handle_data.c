/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:34:17 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/23 23:36:16 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void fill_data(t_cmd comm)
{
    int i;

    i = 0;
    while (i < comm.dt_nb)
    {
        
        comm.dt[i].data = ft_substr(comm.cmd[i], 0, ft_strlen (comm.cmd[i]));
        i++;
    }
        
}
void    handle_data(t_parser *parser)
{
    int i;
    
    i = 0;
    while (i < parser->lex->pipe_nb)
    {
        parser->comm[i].dt = malloc(sizeof(t_data) * parser->comm->dt_nb);
        fill_data(parser->comm[i]);
        i++;
    }

    //----------------print data-----------------//
    // i = 0;
    // int j = 0;
    // while (j < parser->lex->pipe_nb)
    // {
    //     i = 0;
    //     while (i < parser->comm[j].dt_nb)
    //     {
    //         printf ("%s\n", parser->comm[j].dt[i].data);
    //         i++;
    //     }
    //     printf ("%d\n", j);
    //     j++;
    // }
}

// void define_word_token(t_lexer *lex)
// {
//     int i;

//     i = 0;
//     lex->enumerate = (char **) malloc(sizeof (char *) * (lex->word_nb + 1));
//     if (!lex->enumerate)
//         return ;

//     while (lex->word[i])
//     {
//         if (ft_strcmp(lex->word[i], "|") == 0)
//             lex->enumerate[i++] = "PIPE";
//         else if (ft_strcmp(lex->word[i], ">") == 0)
//             lex->enumerate[i++] = "REDIR_OUT";
//         else if (ft_strcmp(lex->word[i], "<") == 0)
//             lex->enumerate[i++] = "REDIR_IN";
//         else if (ft_strcmp(lex->word[i], ">>") == 0)
//             lex->enumerate[i++] = "DREDIR_OUT";
//         else if (ft_strcmp(lex->word[i], "<<") == 0)
//             lex->enumerate[i++] = "HERE_DOC";
//         else
//             lex->enumerate[i++] = "WORD";
//     }
//     lex->enumerate[i] = NULL;
// }