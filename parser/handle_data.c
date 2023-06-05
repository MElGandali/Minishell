/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:34:17 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/05 17:59:20 by maddou           ###   ########.fr       */
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

int ft_check_flag (char *data, int i)
{
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
    if (data[i + 1] == '_' || ft_isalnum(data[i + 1]) == 1)
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
        comm.dt[i].ex_dollar = check_ex_dollar(comm.dt[i].data);
        printf ("%d\n", comm.dt[i].ex_dollar);
        comm.dt[i].position = i;
        define_data(&comm ,comm.dt[i].data, i);
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
            // free(envmnt); //free previous envmnt
            while (tmp->value[i] != '\0')
            {
                *new_data = ft_copier(tmp->value[i], *new_data);
                i++;
            }
            return (1);
        }
        tmp = tmp->next;
    }
    return (0);
}

void expand_data (t_env *env, char *data, int *j, char **new_data)
{
    int i;
    int in;
    (void)new_data;
    (void)env;
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
    check_exit(env, envmnt, new_data);
    *j = --i;
    // else  
    //     *new_data = ft_copier('$', *new_data); 
    free(envmnt);
}

void find_dollar(t_parser *parser, t_cmd *cmd)
{
    (void)parser;
    int i;
    int j;
    char *new_data;

    i = 0;
    while (i < cmd->dt_nb)
    {
        j = 0;
        new_data = NULL;
        while (cmd->dt[i].data[j] != '\0')
        {
            if (cmd->dt[i].data[j] == '$' && check_valid(cmd->dt[i].data, j) == 1)
                expand_data(parser->lex->env, cmd->dt[i].data,  &j, &new_data);
            else
                new_data = ft_copier(cmd->dt[i].data[j], new_data);
            j++;
        }
        free(cmd->dt[i].data);
        cmd->dt[i].data = new_data;
        free (new_data);
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
        printf ("%s\n",parser->comm[i].dt[0].data);
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

// void define_word_token(t_lexer *lex)
// {
//     int i;

//     i = 0;
//     lex->enumerate = (char **) malloc(sizeof (char *) * (lex->word_nb + 1));
//     if (!lex->enumerate)
//         return ;

//     while (lex->word[i])
//     {
//         if (ft_strcmp(lex->word[i], "|") == 0)
//             lex->enumerate[i++] = "PIPE";
//         else if (ft_strcmp(lex->word[i], ">") == 0)
//             lex->enumerate[i++] = "REDIR_OUT";
//         else if (ft_strcmp(lex->word[i], "<") == 0)
//             lex->enumerate[i++] = "REDIR_IN";
//         else if (ft_strcmp(lex->word[i], ">>") == 0)
//             lex->enumerate[i++] = "DREDIR_OUT";
//         else if (ft_strcmp(lex->word[i], "<<") == 0)
//             lex->enumerate[i++] = "HERE_DOC";
//         else
//             lex->enumerate[i++] = "WORD";
//     }
//     lex->enumerate[i] = NULL;
// }