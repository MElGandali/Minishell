/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 23:54:32 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/22 22:10:10 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/fcntl.h>
       

int here_doc(t_parser *parser, t_red *red)
{
    int i;
    char *input;
    char *save_her;
    (void)parser;


    i = 0;
    save_her = NULL;
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
            if (red->ex_dollar == 2)
                input = find_dollar_utils(parser, input, 0, 'e');
            save_her = ft_strjoin(save_her, input);
            save_her = ft_strjoin(save_her, "\n");
            free(input);
        }
    }
    if (save_her != NULL)
        ft_putstr_fd(save_her, red->fd[1]);
    close(red->fd[1]);
    // close(red->fd[0]);
    return (red->fd[0]);
}
int    handle_heredoc(t_parser *parser, int i)
{
    int j;
    int fd_r;

    fd_r = 0;
    if (parser->comm[i].nb_red != 0)
    {
        j = 0;
        while (j < parser->comm->nb_red)
        {
            if (parser->comm[i].red[j].name == 6)
                fd_r = here_doc(parser, &parser->comm[i].red[j + 1]);
            j = j + 2;
        }
    }
    return (fd_r);
}