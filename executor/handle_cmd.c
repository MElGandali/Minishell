/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:47:44 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/08 15:23:15 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"../minishell.h"
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

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
        builtin_commands(parser, i);
    else
    {
        execve((char const*)execpath, parser->comm[i].new_cmd, NULL);
        free(execpath);
        // printf ("bash: %s:", strerror(errno));
            //printf("bash: %s: command not found\n", parser->comm[i].new_cmd[0]);
        ft_putstr_fd("bash: ", 2);
        ft_putstr_fd(parser->comm[i].new_cmd[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        exit(127);
    }
}

void handle_cmd(t_parser *parser)
{
    int fd[2];
    int i;
    int *cid;
    int fd_d;
    int fd_her;
    int e_code = 0;
    
    i = 0;
    cid = malloc(sizeof (int) * parser->lex->pipe_nb);
    if (parser->lex->pipe_nb > 1)
    {
        while (i < parser->lex->pipe_nb)
        {
            if (open_redirect(parser->comm, i) == 0)
            {

            fd_her = 0;
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
                
                    if (parser->comm[i].nb_red > 0)
                        check_redirect(&parser->comm[i], fd_her);
                    if (parser->comm[i].new_cmd != NULL)
                    {
                        exec_cmd(parser, i);
                        if (is_builtin(parser->comm[i].new_cmd) == 0)
                            exit(0);
                    }
                    else
                        exit(0);
                
            }
            if (i > 0)
                close(fd_d);
            fd_d = fd[0];
            close(fd[1]);
            }
            i++;
        }
        i = 0;
        while (i < parser->lex->pipe_nb)
        {
            waitpid(cid[i], &e_code, 0);
            if (WIFSIGNALED(e_code))
                g_exit = WTERMSIG(e_code) + 128;
            else if (WIFEXITED(e_code))
                g_exit = WEXITSTATUS(e_code);
            i++;
        }
    }
    else 
    {
        if (parser->comm[0].new_cmd != NULL && is_builtin(parser->comm[i].new_cmd) == 0)
        {
            fd_her = handle_heredoc(parser, i);
            if (open_redirect(parser->comm, i) == 0)
            {
                cid[0] = fork();
                if (cid[0] == 0)
                {
                    // dup2(fd_her, 0);
                    // close (fd_her);
                    if (parser->comm[0].nb_red > 0)
                        check_redirect(&parser->comm[0], fd_her);
                    builtin_commands(parser, i);
                    exit (0);
                }
                waitpid(cid[0], &e_code, 0);
                if (WIFSIGNALED(e_code))
                    g_exit = WTERMSIG(e_code) + 128;
                else if (WIFEXITED(e_code))
                    g_exit = WEXITSTATUS(e_code);
            }
        }
        else
        {
            fd_her = handle_heredoc(parser, i);
            if (fd_her != 0)
            {
                // close(fd_her); //3lach dart hadi
            }
            if (open_redirect(parser->comm, i) == 0)
            {
                cid[0] = fork();
                if (cid[0] == 0)
                {
                    // dup2(fd_her, 0); 3lach dart hadi
                    // close (fd_her);
                    if (parser->comm[0].nb_red > 0)
                        check_redirect(&parser->comm[0], fd_her);
                    if (parser->comm[0].new_cmd != NULL)
                        exec_cmd(parser, 0);
                    else
                        exit(0);
                }
                waitpid(cid[0], &e_code, 0);
                if (WIFSIGNALED(e_code))
                    g_exit = WTERMSIG(e_code) + 128;
                else if (WIFEXITED(e_code))
                    g_exit = WEXITSTATUS(e_code);
            }
        }
    }
}