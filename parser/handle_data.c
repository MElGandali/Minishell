/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:34:17 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/10 01:46:29 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <string.h>

int  find_data_redir(int *name, char *data)
{
    if (ft_strnstr(data, "<<") == 0)
        *name = HERE_DOC;
    else if (ft_strnstr(data, "<") == 0)
        *name = REDIR_IN;
    else  if (ft_strnstr(data, ">>") == 0)
        *name = DREDIR_OUT;
    else if  (ft_strnstr(data, ">") == 0)
        *name = REDIR_OUT;
    else  
        return (1);
    return (0);
}

int check_quote(char *data, int i)
{
    char c;
    
    if (data[i] == '\'' || data[i] == '\"')
    {
        c = data[i];
        while (data[i] != '\0' && data[i] == c)
            i++;
        if (data[i] == '\0')
            return (0); 
    }
    return (1);
}

int ft_check_flag (char *data, int i)
{
    // while (data[i] != '\0' && (data[i] == '\'' || data[i] == '\"'))
    // {
    //     if (data[i] == '\'' || data[i] == '\"')
    //         i = skip_quote(data, i);
    //     i++;
    // }
    // if (data[i] == '\0')
    //     return (0);
    if (check_quote(data, i) == 0)
        return 0;
    i = 0;
    while (data[i] != '\0' && (data[i] == '\'' || data[i] == '\"'))
    {
        if (data[i] == '\'')
        {
            while (data[i] == '\'')
                i++;
            if (data[i + 1] != '\"')
              break;
        }
        if (data[i] == '\"')
        {
            while (data[i] == '\"')
                i++;
            if (data[i + 1] != '\'')
              break;
        }
        i++;
    }
    if (data[i + 1] == '-')
        return (1);
    return (0);
}

void check_pos_one(t_cmd *comm, char *data, int pos)
{
    int i;
    
    i = 0;
    if (comm->dt[0].name == COMMAND && pos == 1)
    {
        if (ft_check_flag (data, i) == 1)
            comm->dt[pos].name = FLAG;
        else if (data[0] == '-')
             comm->dt[pos].name = FLAG;
        else if (find_data_redir(&comm->dt[1].name, data) == 1)
            comm->dt[1].name = WORD;
    }
    else if (comm->dt[0].name != COMMAND && pos == 1)
    {
            if (comm->dt[0].name == HERE_DOC)
                comm->dt[pos].name = DELIMITER;
            else
                comm->dt[pos].name = DOC;      
    }
}

void define_data(t_cmd *comm, char *data, int pos)
{
    if (pos == 0)
    {
        if (find_data_redir (&comm->dt[0].name, data) == 0)
            return ;
        else
        {
            comm->nb_cmd = 1;
            comm->dt[0].name = COMMAND;
        }
    }
    else
       check_pos_one(comm, data, pos);
    if (pos > 1)
    {
            printf ("hna\n");
        if (comm->dt[pos - 1].name == FLAG && data[0] == '-')
           comm->dt[pos].name = FLAG;
        else if ((comm->dt[pos - 1].name == DOC || comm->dt[pos - 1].name == DELIMITER) && comm->nb_cmd == 0 && data[0] != '<' && data[0] != '>')
        {
            comm->nb_cmd = 1;
            comm->dt[pos].name = COMMAND;
        }
        else if (find_data_redir(&comm->dt[pos - 1].name, comm->dt[pos - 1].data) == 0)
        {
            if (comm->dt[pos - 1].name == HERE_DOC)
                comm->dt[pos].name = DELIMITER;
            else
                comm->dt[pos].name = DOC;
        }
        else if (find_data_redir(&comm->dt[pos].name, data) == 0)
            return ;
        else
        {
            comm->dt[pos].name = WORD;
        }
    }
}

int check_valid(char *data, int i)
{
    if ((data[i + 1] == '_' || ft_isalnum(data[i + 1]) == 1 
        || data[i + 1] == '\'' || data[i + 1] == '\"'))
        return (1);
    return (0);
}

int x(char *data, char c, int j)
{
    ++j;
    while(data[j] != c)
    {
        if (data[j] == '$')
        {
            if (c == '\"')
            {
                if (check_valid(data, j) == 1)
                    return (1);
            }
        }
        j++;
    }
    return (0);
}



int check_ex_dollar(char *data)
{
    int i;
    int j;

    i = 0;
    while (data[i] != '\0')
    {
        j = i;
        if (data[i] == '\'')
        {
            i++;
            quote(data, &i);
            if (x(data, data[j], j) == 1)
                return (1);
        }
        else if (data[i] == '\"')
        {
            i++;
            dquote(data, &i);
            if (x(data, data[j], j) == 1)
                return (1);
        }
        else if (data[i] == '$')
        {
            if (check_valid(data, i) == 1)
                return (1);
        }
        i++;
    }
    return (0);
}

void fill_data(t_cmd comm)
{
    int i;

    i = 0;
    // printf ("%d\n", comm.dt_nb);
    while (i < comm.dt_nb)
    {
        // printf ("%s %d\n", comm.cmd[i], ft_strlen (comm.cmd[i]));
        comm.dt[i].data = ft_substr(comm.cmd[i], 0, ft_strlen (comm.cmd[i]));
        comm.dt[i].copy_data = ft_substr(comm.cmd[i], 0, ft_strlen (comm.cmd[i]));
        // printf ("%s\n", comm.dt[i].copy_data );
        // comm.dt[i].position = i;
        define_data(&comm ,comm.dt[i].data, i);
        if (i == 0 || (i > 0 && ft_strcmp("<<", comm.dt[i - 1].data) != 0))
            comm.dt[i].ex_dollar = check_ex_dollar(comm.dt[i].data);
        else   
           comm.dt[i].ex_dollar = 0;
        // printf ("%d\n", comm.dt[i].ex_dollar);
        // printf ("data %s position %d dfine %d\n", comm.dt[i].data,comm.dt[i].position, comm.dt[i].name);
        i++;
    }
    
}

char *ft_copier(char add, char *new_data)
{
    int nb;
    int i;
    char *new;
    
    nb = 0;
    i = 0;
    if(new_data != NULL)
        nb = ft_strlen(new_data);
    new = malloc(sizeof(char) * (nb + 2));// EOL + char add
    if (!new)
        return (0);
    if (new_data != NULL)
    {
        while (new_data[i] != '\0')
        {
            new[i] = new_data[i];
            i++;
        }
    }
    new[i++] = add;
    new[i] = '\0';
    free(new_data);
    return (new);
}

int check_exit(t_env *env, char *envmnt, char **new_data)
{
    t_env *tmp;
    int i;

    tmp = env;
    i = 0;
    while (tmp != NULL)
    {
        if (ft_strcmp(tmp->key, envmnt) == 0)
        {
            while (tmp->value[i] != '\0')
            {
                *new_data = ft_copier(tmp->value[i], *new_data);
                i++;
            }
            return (1);
        }
        // else
        //     *new_data = ft_strdup(envmnt);
        tmp = tmp->next;
    }
    return (0);
}

void expand_data (t_env *env, char *data, int *j, char **new_data)
{
    int i;
    int in;
    char *envmnt;

    in = 0;
    i = *j + 1;
    envmnt = NULL;
    while (data[i] != '\0')
    {
        if (data[i] == '_' || ft_isalnum(data[i]) == 1)
            envmnt = ft_copier(data[i], envmnt);
        else
            break;
        i++;
    }
    if (envmnt != NULL)
        check_exit(env, envmnt, new_data);
    *j = --i;
    free(envmnt);
}
void check_dollar(t_parser *parser, char *dquote, char **new_data)
{
    int i;

    i = 0;
    while (dquote[i] != '\0')
    {
        if (dquote[i] == '$' && dquote[i + 1] != '?')
        {
            if (dquote[i + 1] == ' ')
                *new_data = ft_copier(dquote[i], *new_data);
            else if (dquote[i + 1] == '_' || ft_isalnum(dquote[i + 1]) == 1)
                expand_data(parser->lex->env, dquote, &i, new_data);
            else if (dquote[i + 1] != '\"' && !(dquote[i] == '_' || ft_isalnum(dquote[i]) == 1))  
                i++;
            else  
                *new_data = ft_copier(dquote[i], *new_data);
        }
        else  
            *new_data = ft_copier(dquote[i], *new_data);
        i++;
    }
}

void copy_quote(char *data, int *i, char **new_data)
{
    *new_data = ft_copier('\'', *new_data);
    (*i)++;
    while (data[*i] != '\'')
    {
        *new_data = ft_copier(data[*i], *new_data);
        (*i)++;
    }
    *new_data = ft_copier('\'', *new_data);
    // printf ("%s\n", *new_data);
    // if (data[*i] == '\0')
    //     (*i)--;
}
// char *copy_dquote (t_parser *parser, t_cmd *cmd, int i, int *j)
// {
//     char *new_data;

   
// }

void find_dollar(t_parser *parser, t_cmd *cmd)
{
    int i;
    int j;
    char *new_data;
    char *dquote;

    i = 0;
    while (i < cmd->dt_nb)
    {
        j = 0;
        new_data = NULL;
        while (cmd->dt[i].data[j] != '\0')
        {
            dquote = NULL;
            if (cmd->dt[i].data[j] == '\'')
                copy_quote(cmd->dt[i].data, &j, &new_data);
            if (cmd->dt[i].data[j] == '\"')
            {
                dquote = ft_copier(cmd->dt[i].data[j], dquote);
                j++; // squipe quote
                while (cmd->dt[i].data[j] != '\"')
                    dquote = ft_copier(cmd->dt[i].data[j++], dquote);
                dquote = ft_copier(cmd->dt[i].data[j], dquote);
                check_dollar(parser, dquote, &new_data);
            }
            else   
            {
                if ( cmd->dt[i].data[j]== '$' && cmd->dt[i].data[j + 1] != '\0' && cmd->dt[i].data[j + 1] != '?')
                {
                    if (cmd->dt[i].data[j] == ' ')
                        new_data = ft_copier(cmd->dt[i].data[j + 1], new_data);
                    else if (cmd->dt[i].data[j + 1] == '_' || ft_isalnum(cmd->dt[i].data[j + 1]) == 1)
                        expand_data(parser->lex->env, cmd->dt[i].data, &j, &new_data);
                    else if (!(cmd->dt[i].data[j + 1] == '_' 
                    || ft_isalnum(cmd->dt[i].data[j + 1]) == 1) 
                    && cmd->dt[i].data[j + 1] != '\0' && cmd->dt[i].data[j + 1] != '\''
                     && cmd->dt[i].data[j + 1] != '\"')  
                        j++;
                    else if (cmd->dt[i].data[j + 1] != '\''
                     && cmd->dt[i].data[j + 1] != '\"') 
                        new_data = ft_copier(cmd->dt[i].data[j], new_data);
                }
                else if (cmd->dt[i].data[j] != '\''
                     && cmd->dt[i].data[j] != '\"')
                    new_data = ft_copier(cmd->dt[i].data[j], new_data);
            }            
            j++;
        }
        printf ("%s\n", new_data);
        i++;
    }
    // while (i < cmd->dt_nb)
    // {
    //     j = 0;
    //     new_data = NULL;
        // while (cmd->dt[i].data[j] != '\0')
        // {
        //     if (cmd->dt[i].ex_dollar == 1 && cmd->dt[i].data[j] == '$' && check_valid(cmd->dt[i].data, j) == 1)
        //     {
        //         expand_data(parser->lex->env, cmd->dt[i].data,  &j, &new_data);
        //         printf ("%d\n", j);
        //     }
        //     else if (cmd->dt[i].data[j] == '\'')
        //     {
        //         j++;
        //         copy_quote(cmd->dt[i].data, &j, &new_data);
        //     }
        //     else
        //         new_data = ft_copier(cmd->dt[i].data[j], new_data);
        //     j++;
        // }
        // // free(cmd->dt[i].data);
        // if (new_data == NULL)
        // {
        //     printf ("x");
        //     cmd->dt[i].name = WALLO;
        //     cmd->dt[i].data = NULL;
        // }
        // else 
        // {
        //     // free(cmd->dt[i].data);
        //     cmd->dt[i].data = ft_strdup(new_data);
        // }
        // // printf ("%s\n",cmd->dt[i].data);
        // free (new_data);
        // i++;
    // }
    i = 0;
    // while (cmd->dt[0].data[i] != '\0')
    // {
    //     // if (cmd->dt[i].data != NULL)
    //         printf ("%c", cmd->dt[0].data[i]);
    //     i++;
    // }
    // printf ("\n");
}

void    handle_data(t_parser *parser)
{
    int i;
    
    i = 0;
    while (i < parser->lex->pipe_nb)
    {
        parser->comm[i].dt = malloc(sizeof(t_data) * parser->comm[i].dt_nb);
        fill_data(parser->comm[i]);
        find_dollar(parser, &parser->comm[i]);
        i++;
    }
    
    // while (parser->comm[i].cmd[j])
    // {
    //     free()
    //     j++;
    // }
    // expaind_dollar(parser);
    //----------------print data-----------------//
    // i = 0;
    // int j = 0;
    // while (j < parser->lex->pipe_nb)
    // {
    //     i = 0;
    //     while (i < parser->comm[j].dt_nb)
    //     {
    //         printf ("%s\n", parser->comm[j].dt[i].data);
    //         i++;
    //     }
    //     printf ("%d\n", j);
    //     j++;
    // }
}