/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:32:14 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/09 15:29:05 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_multi_arg(char **redirect)
{
    int i;
    int j;
    char *check_name;
    int check_null;
    int check_char;

    i = 0;
    check_null = 0;
    check_char = 0;
    while (redirect[i] != NULL)
    {
        j = 0;
        check_name = NULL;
        while (redirect[i][j] != '\0')
        {
            if (redirect[i][j] == '\'' || redirect[i][j] == '\"')
                check_name = if_quote_fill(redirect[i], &j, check_name);
            else  
                check_name = ft_copier(redirect[i][j], check_name);
            j++;
        }
        if (check_name != NULL)
            check_char++;
        // else   
        //     check_char++;
        // ft_printf ("%d \n", check_char);
        free(check_name);
        i++;
    }
    if (check_char == 0 || check_char > 1)
        return (1);
    return (0);
}

char *expand_name_file(t_red *red, char **check_redirect)
{
    int i;
    int j;
    char *new_name;

    i = 0;
    free(red->data);
    red->data = NULL;
    while (check_redirect[i] != NULL)
    {
        j = 0;
        new_name = NULL;
        while (check_redirect[i][j] != '\0')
        {
            if (check_redirect[i][j] == '\'' || check_redirect[i][j] == '\"')
                new_name = if_quote_fill(check_redirect[i], &j, new_name);
            else    
                new_name = ft_copier(check_redirect[i][j], new_name);
            j++;
        }
        red->data = ft_strjoin(red->data, new_name);
        // free (new_name); leaks check ...
        i++;
    }
    return (red->data);
}
int check_ambiguous(t_red *red)
{
    int i;
    // int j;
    char **check_redirect;
    char *data;
    int check;

    i = 0;
    data = NULL;
    if (red->data == NULL)
        return 1;
    if (red->data[i] == '\0')
        return (1);
    while(red->data[i] != '\0')
    {
        if (red->data[i] == '\"' || red->data[i] == '\'')
            i = skip_quote(red->data, i);
        else if (red->data[i] == ' ' || red->data[i] == '\t' || red->data[i] == '\n')
            red->data[i] = '\n';
        i++;
    }
    check_redirect = ft_split(red->data, '\n', &check);
    if (check == 0)
        return (1);
    else if (check > 1)
    {
        if (check_multi_arg(check_redirect) == 1)
            return (1);
    }
    else if (check == 1)
    {
        i = 0;
        while (check_redirect[0][i] != '\0')
        {
            if (ft_isprint(check_redirect[0][i]) == 1 && check_redirect[0][i] !='\"' 
                && check_redirect[0][i] !='\'' && check_redirect[0][i] !=' ' &&
                check_redirect[0][i] != '\t')
                {
                    red->data = expand_name_file(red, check_redirect);
                    return (0);
                }
            i++;
        }
        return (1);
    }
    red->data = expand_name_file(red, check_redirect);
    return (0);
}

int open_redir_in(t_cmd *cmd, int i)
{
    int fd;
    
    if (check_ambiguous(&cmd->red[i + 1]) == 1)
    {
        ft_printf (" ambiguous redirect\n");
        return (1);
    }
    fd = open(cmd->red[i + 1].data, O_RDONLY , 0644);
    if (fd < 0)
    {
        g_exit = 1;
        ft_printf("bash: %s: %s\n",cmd->red[i + 1].data, strerror(errno));
        return(1);
    }
    if (access(cmd->red[i + 1].data,F_OK | R_OK ) == -1)
    {
        g_exit = 1;
        close(fd);
        ft_printf("bash: %s: %s",cmd->red[i + 1].data, strerror(errno));
        return (1);
    }
    close(fd); //
    return (0);
}

int open_dredir_out(t_cmd *cmd, int i)
{
    int fd;
    if (check_ambiguous(&cmd->red[i + 1]) == 1)
    {
        ft_printf (" ambiguous redirect\n");
        return (1);
    }
    fd = open(cmd->red[i + 1].data, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
    {
        g_exit = 1;
        ft_printf("bash: %s: %s",cmd->red[i + 1].data, strerror(errno));
        return(1);
    }
    if (access(cmd->red[i + 1].data,F_OK | W_OK ) == -1)
    {
        g_exit = 1;
        close(fd);
        ft_printf("bash: %s: %s",cmd->red[i + 1].data, strerror(errno));
        return (1);
    }
    close(fd); //
    return (0);
}
int open_redir_out(t_cmd *cmd, int i)
{
    int fd;
    
    if (check_ambiguous(&cmd->red[i + 1]) == 1)
    {
        ft_printf (" ambiguous redirect\n");
        return (1);
    }
    fd = open(cmd->red[i + 1].data, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd < 0)
    {
        g_exit = 1;
        ft_printf("bash: %s: %s",cmd->red[i + 1].data, strerror(errno));
        return(1);
    }
    if (access(cmd->red[i + 1].data,F_OK | W_OK ) == -1)
    {
        g_exit = 1;
        close(fd);
        ft_printf("bash: %s: %s",cmd->red[i + 1].data, strerror(errno));
        return (1);
    }
    close(fd); //
    return (0);
}

int open_redirect(t_cmd *cmd, int i)
{
    int j;
    j = 0;
    while (j < cmd[i].nb_red)
    {
        if (cmd[i].red[j].name == 4)
        {
            if (open_redir_in(&cmd[i], j) == 1)
            {
                return (1);
            }
            j++;
        }
        else if (cmd[i].red[j].name == 5)
        {
            if (open_redir_out(&cmd[i], j) == 1)
                return (1);
            j++;
        }
        else if (cmd[i].red[j].name == 7)
        {
            if (open_dredir_out(&cmd[i], j) == 1)
                return (1);
            j++;
        }
        j++;
    }
    return (0);
}