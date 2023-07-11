/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:47:44 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/11 18:28:28 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"../minishell.h"

int    is_builtin(char **cmd)
{
    int i;
    
    i = 0;
    if (cmd[0]!= NULL &&( ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "cd") == 0
        || ft_strcmp(cmd[0], "exit") == 0 || ft_strcmp(cmd[0], "pwd") == 0
        || ft_strcmp(cmd[0], "$?") == 0 || ft_strcmp(cmd[0], "export") == 0
        || ft_strcmp(cmd[0], "env") == 0 || ft_strcmp(cmd[0], "unset") == 0 ))
        return (0);  
    return (1);
}
int check_path(char *command)
{
    int i;

    i = 0;
    if (command == NULL)
        return (0);
    while (command[i] != '\0')
    {
        if (command[i] == '/')
            return (1);
        i++;
    }
    return (0);
}

void    exec_cmd(t_parser *parser, int i)
{
    char *execpath;
    if (check_path(parser->comm[i].new_cmd[0]) == 0)
        execpath = (char*)find_execpath(parser, i);
    else  
        execpath = ft_strdup(parser->comm[i].new_cmd[0]);
    if (is_builtin(parser->comm[i].new_cmd) == 0)
        builtin_commands(parser, i);
    else
    {
        execve((char const*)execpath, parser->comm[i].new_cmd, parser->lex->ar_env);
        if (execpath != NULL && execpath[0] == '/')
        {
            ft_putstr_fd("bash: ", 2);
            ft_putstr_fd(parser->comm[i].new_cmd[0], 2);
            ft_putstr_fd(": ", 2);
            ft_putstr_fd(strerror(errno), 2);
            ft_putstr_fd("\n", 2);
            free(execpath);
            exit (127);
        } 
        ft_putstr_fd("bash: ", 2);
        ft_putstr_fd(parser->comm[i].new_cmd[0], 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd("command not found", 2);
        ft_putstr_fd("\n", 2);
        free(execpath);
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
    int terminal_fd;
    
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
                        if (parser->comm[i].new_cmd[0] != NULL)
                        {
                            exec_cmd(parser, i);
                            if (is_builtin(parser->comm[i].new_cmd) == 0)
                                exit(0);
                        }
                        else
                        {
                            execve(NULL, parser->comm[i].new_cmd, parser->lex->ar_env);
                            ft_putstr_fd("bash: ", 2);
                            ft_putstr_fd(parser->comm[i].new_cmd[0], 2);
                            // ft_putstr_fd(": ", 2);
                            ft_putstr_fd("command not found", 2);
                            ft_putstr_fd("\n", 2);
                            exit(127);
                        }
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
                if (parser->comm[0].nb_red > 0)
                    check_redirect(&parser->comm[0], fd_her);
                builtin_commands(parser, i);
                terminal_fd = open("/dev/tty", O_WRONLY);
                dup2(terminal_fd, 1);
                close(terminal_fd);
            }
        }
        else
        {
            fd_her = handle_heredoc(parser, i);
            if (open_redirect(parser->comm, i) == 0)
            {
                cid[0] = fork();
                if (cid[0] == 0)
                {
                    if (parser->comm[0].nb_red > 0)
                        check_redirect(&parser->comm[0], fd_her);
                    if (parser->comm[0].new_cmd != NULL)
                        exec_cmd(parser, 0);
                    else
                        exit (0);
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