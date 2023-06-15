/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:54:09 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/15 23:40:57 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int check_redir_io(t_cmd comm)
{
    int i;

    i = 0;
    while (i < comm.nb_red)
    {
        if (comm.red[i].name == REDIR_IN || comm.red[i].name == REDIR_OUT
            || comm.red[i].name == DREDIR_OUT)
            return (0);
        i++;
    }
    return (1);
}

void    open_redir_io(t_parser *parser, int i)
{
    
    if (parser->comm[i].nb_cmd != 0)
        exec_cmd(parser, i);
}