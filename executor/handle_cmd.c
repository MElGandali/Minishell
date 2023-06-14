/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:47:44 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/14 15:19:12 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int    is_builtin(char **cmd)
{
    int i;
    
    i = 0;
    if (ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "cd") == 0 
        || ft_strcmp(cmd[0], "exit") == 0 || ft_strcmp(cmd[0], "unset") == 0
        || ft_strcmp(cmd[0], "pwd") == 0 || ft_strcmp(cmd[0], "pwd") == 0 
        || ft_strcmp(cmd[0], "$?") == 0 || ft_strcmp(cmd[0], "export") == 0
        || ft_strcmp(cmd[0], "env") == 0)
        return (0);  
        
    return (1);
}

void    single_cmd(t_parser *parser)
{
        if (is_builtin(parser->comm->new_cmd) == 0)
                g_exit = builtin_commands(parser);
        else
        {
            if (execve(parser->comm->new_cmd[0], parser->comm->new_cmd, NULL) == -1)
                strerror(errno);
        }
        // exit (g_exit);
}

// void    multiple_cmd(t_parser *parser)
// {
    
// }

void handle_cmd(t_parser *parser)
{
    single_cmd(parser);
    // multiple_cmd(parser);   
    // execute_cmd(parser);
}