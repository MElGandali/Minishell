/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 23:54:32 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/12 22:40:52 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
       

void here_doc(t_red *red)
{
    int i;
    char *input;
    char *save_her;


    i = 0;
    red->fd = malloc (sizeof(int) * 2 + 1);
    if (pipe(red->fd) == -1)
    {
        perror("pipe");
        exit(2);
    }
    while (1)
    {
        input = readline("> ");
        if (ft_strcmp(input, red->data) == 0)
            break;
        else
        {
            // if $ env variables exist , expand input
            save_her = ft_strjoin(input, "\n");
            free(input);
        }
    }
    write(red->fd[1], &save_her , ft_strlen(save_her));
    // red->fd[2] = '\0';
    // close(red->fd[1]);
    // close(red->fd_her[0]);
}
void    handle_heredoc(t_parser *parser)
{
    int i;
    int j;

    i = 0;
    if (parser->comm->nb_red != 0)
    {
        while (i < parser->lex->pipe_nb)
        {
            j = 0;
            while (j < parser->comm->nb_red)
            {
                if (parser->comm[i].red[j].name == 6)
                    here_doc(&parser->comm[i].red[j + 1]);
                j = j + 2;
            }
            i++;
        }
    }
}