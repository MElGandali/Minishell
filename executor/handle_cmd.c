/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:47:44 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/22 15:30:49 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"../minishell.h"

int    is_builtin(char **cmd)
{
    int i;
    
    i = 0;
    if (ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "cd") == 0
        || ft_strcmp(cmd[0], "exit") == 0 || ft_strcmp(cmd[0], "pwd") == 0
        || ft_strcmp(cmd[0], "$?") == 0 || ft_strcmp(cmd[0], "export") == 0
        || ft_strcmp(cmd[0], "env") == 0 || ft_strcmp(cmd[0], "unset") == 0 )
        return (0);  
        
    return (1);
}

void    exec_cmd(t_parser *parser, int i)
{
    char *execpath;
    int ret;
    ret = 0;
    
    execpath = (char*)find_execpath(parser, i);
    if (is_builtin(parser->comm[i].new_cmd) == 0)
        g_exit = builtin_commands(parser, i);
    else
    {
        if (execve((char const*)execpath, parser->comm[i].new_cmd, NULL) == -1)
        {
            free(execpath);
            printf("bash: %s: command not found\n", parser->comm[i].new_cmd[0]);
            g_exit = 127;
            ret = -1;
        }
    }
}

void handle_cmd(t_parser *parser)
{
    int fd[2];
    int i;
    int *cid;
    int fd_d;
    int fd_her;
    
    i = 0;
    cid = malloc(sizeof (int) * parser->lex->pipe_nb);
    while (i < parser->lex->pipe_nb)
    {
        if (i < parser->lex->pipe_nb - 1)
        {
            if (pipe(fd) == -1)
            {
                perror("pipe");
                exit(2);
            }
        }
        fd_her = handle_heredoc(parser, i);
        cid[i] = fork();
        if (cid[i] == 0)
        {
            if (i != 0)
            {
                dup2(fd_d, 0);
                close(fd_d);
            }
            if (i != parser->lex->pipe_nb - 1)
            {
                dup2(fd[1], 1);
                close(fd[1]);
            }
            if (parser->comm[i].new_cmd != NULL)
                exec_cmd(parser, i);
        }
        if (i > 0)
            close(fd_d);
        fd_d = fd[0];
        close(fd[1]);
        i++;
    }
    i = 0;
    while (i < parser->lex->pipe_nb)
    {
        waitpid(cid[i], &g_exit, 0);
        i++;
    }
}
                // if (check_redir_io(parser->comm[i]) == 0)
                // {
                //     j = 0;
                //     while (j < parser->comm[i].dt_nb)
                //     {
                //         open_redir_io(parser, i);
                //         j++;
                //     }
                // }