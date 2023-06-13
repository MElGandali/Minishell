/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 23:32:44 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/13 22:19:34 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void    executor(t_parser *parser)
{
    // TO DO LIST
    // 1- handle redirections
    // 2- check if the cmd is a builtin or not
    // 4- if there are more than one cmd fork and execute with execve
    // handle_heredoc(parser);
    handle_cmd(parser);
    
    //      char *buff = malloc(sizeof (char) * 10);
    // int nb = read(parser->comm->red->fd[0], buff, 10);
//    buff[nb] = '\0';
//    printf("%s\n", buff);
}