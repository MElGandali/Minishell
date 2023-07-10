/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:34:17 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/10 18:06:11 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
            comm->dt[pos].name = WORD;
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

int ft_check_expand_delimiter(char *delimiter)
{
    int i;

    i = 0;
    while (delimiter[i] != '\0')
    {
        if (delimiter[i] == '\'' || delimiter[i] == '\"')
            return (0);
        i++;
    }
    return (1);
}

void fill_data(t_cmd comm)
{
    int i;

    i = 0;
    while (i < comm.dt_nb)
    {
        comm.dt[i].data = ft_substr(comm.cmd[i], 0, ft_strlen (comm.cmd[i]));
        comm.dt[i].copy_data = ft_substr(comm.cmd[i], 0, ft_strlen (comm.cmd[i]));
        define_data(&comm ,comm.dt[i].data, i);
        if (i == 0 || (i > 0 && ft_strcmp("<<", comm.dt[i - 1].data) != 0))
            comm.dt[i].ex_dollar = check_ex_dollar(comm.dt[i].data);
        else if (i > 0 && ft_strcmp("<<", comm.dt[i - 1].data) == 0)
        {
            if (ft_check_expand_delimiter(comm.dt[i].data) == 1)
                comm.dt[i].ex_dollar = 2;
            else  
                comm.dt[i].ex_dollar = 0;
        }
        else   
            comm.dt[i].ex_dollar = 0;
        i++;
    }
    
    /************************PRINT CHECK_EXPAND******************/
    // i = 0;
    // while (i < 2)
    // {
    //     ft_printf ("%s\n", comm.cmd[i]);
    //     i++;
    // }
    /************************PRINT CHECK_EXPAND******************/
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
            while (tmp->value != NULL && tmp->value[i] != '\0') //mochkil min ikon fih null f command echo $x x= katban
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

char *copy_quote(char *data, int *i, char *new_data)
{
    new_data = ft_copier('\'', new_data);
    (*i)++;
    while (data[*i] != '\'')
    {
        new_data = ft_copier(data[*i], new_data);
        (*i)++;
    }
    new_data = ft_copier('\'', new_data);
    return (new_data);
}

char *find_dollar_utils(t_parser *parser, char *data, int j, char e)
{
    char *new_data;
    char *dquote;
    
    new_data = NULL;
    if (data == NULL)
        return (data);
    while (data[j] != '\0')
    {
        dquote = NULL;
        if (e == 'n' && data[j] == '\'')
            new_data = copy_quote(data, &j, new_data);
        if (e == 'e' && data[j] == '\'')
        {
            dquote = copy_quote(data, &j, new_data);
            check_dollar(parser, dquote, &new_data);
        }
        if (data[j] == '\"')
        {
            dquote = ft_copier(data[j], dquote);
            j++; // squipe quote
            while (data[j] != '\"')
                dquote = ft_copier(data[j++], dquote);
            dquote = ft_copier(data[j], dquote);
            check_dollar(parser, dquote, &new_data);
        }
        else  
        {
            if ( data[j]== '$' && data[j + 1] != '\0' && data[j + 1] != '?')
            {
                if (data[j] == ' ')
                    new_data = ft_copier(data[j + 1], new_data);
                else if (data[j + 1] == '_' || ft_isalnum(data[j + 1]) == 1)
                    expand_data(parser->lex->env, data, &j, &new_data);
                else if (!(data[j + 1] == '_' 
                || ft_isalnum(data[j + 1]) == 1) 
                && data[j + 1] != '\0' && data[j + 1] != '\''
                 && data[j + 1] != '\"')  
                    j++;
                else if (data[j + 1] != '\''
                 && data[j + 1] != '\"') 
                    new_data = ft_copier(data[j], new_data);
            }
            else if (data[j] != '\''
                && data[j] != '\"')
                new_data = ft_copier(data[j], new_data);
        }            
        j++;
    }
    return (new_data);
}
void find_dollar(t_parser *parser, t_cmd *cmd)
{
    int i;
    int j;
    char *new_data;

    i = 0;
    while (i < cmd->dt_nb)
    {
        j = 0;
        new_data = NULL;
        if (cmd->dt[i].name != 10 && cmd->dt[i].name != 4
            && cmd->dt[i].name != 5 && cmd->dt[i].name != 6
            && cmd->dt[i].name != 7)
        {
            new_data = find_dollar_utils(parser, cmd->dt[i].data, j, 'n');
            if (new_data == NULL)
            {
                cmd->dt[i].name = WALLO;
                cmd->dt[i].data = NULL;
            }
            else 
            {
                free(cmd->dt[i].data);
                cmd->dt[i].data = ft_strdup(new_data);
            }
        }
        i++;
    }
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
        handal_wildcard(parser, &parser->comm[i]);
        i++;
    }
    // free_parser(parser);
    // expaind_dollar(parser);
    //----------------print data-----------------//
    // i = 0;
    // int j = 0;
    // while (j < parser->lex->pipe_nb)
    // {
    //     i = 0;
    //     while (i < parser->comm[j].dt_nb)
    //     {
    //         ft_printf ("%s\n", parser->comm[j].dt[i].data);
    //         i++;
    //     }
    //     ft_printf ("%d\n", j);
    //     j++;
    // }
}
