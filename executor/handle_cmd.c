/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:47:44 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/16 18:43:24 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"
#include <sys/wait.h>
#include <unistd.h>

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

void    exec_cmd(t_parser *parser, int i)
{
    char *execpath;
    int cid;
    int *ret;
    int fd[2];
    
    ret = 0;
    
    
    execpath = (char*)find_execpath(parser);
    if (is_builtin(parser->comm[i].new_cmd) == 0)
        g_exit = builtin_commands(parser, i);
    else
    {
        cid = fork();
        if (cid == 0)
        {
            if (execve((char const*)execpath, parser->comm[i].new_cmd, NULL) == -1)
            {
                free(execpath);
                printf("bash: %s: command not found\n", parser->comm[i].new_cmd[0]);
                g_exit = 127;
                *ret = -1;
            }
        }
        waitpid(cid, NULL, 0);
        if (*ret == 0)
        {
            free(execpath);
            g_exit = 0;
        }
    }
}

void handle_cmd(t_parser *parser)
{
    int *fd;
    int i;
    int j;
    int cid;
    int fd_r;
    
    i = 0;
    j = 0;
    fd = 0;
    cid = 0;
    fd_r = 0;
    
    if (parser->lex->pipe_nb != 1)
    {
        if (pipe(fd) == -1)
        {
            perror("pipe");
            exit(2);
        }
        while (i < parser->lex->pipe_nb)
        {
            cid = fork();
            if (cid == 0)
            {
                dup2(fd[1], 1);
                if (check_redir_io(parser->comm[i]) == 0)
                {
                    j = 0;
                    while (j < parser->comm[i].dt_nb)
                    {
                        open_redir_io(parser, i);
                        j++;
                    }
                }
                else
                    exec_cmd(parser, i);
            }
            waitpid(cid, NULL, 0);
            // fd_r = fd[1];
            dup2(fd[0], 0);
        i++;    
        }
        close(fd[0]);
        close(fd[1]);
    }
    else
        exec_cmd(parser, i);
}