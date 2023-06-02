/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:34:17 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/02 22:10:46 by maddou           ###   ########.fr       */
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
void check_dolar(char *data)
{
    
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
        check_dolar(comm.dt[i].data);
        comm.dt[i].position = i;
        define_data(&comm ,comm.dt[i].data, i);
        printf ("data %s position %d dfine %d\n", comm.dt[i].data,comm.dt[i].position, comm.dt[i].name);
        i++;
    }
    i = 0;

}

void    handle_data(t_parser *parser)
{
    int i;
    
    i = 0;
    while (i < parser->lex->pipe_nb)
    {
        parser->comm[i].dt = malloc(sizeof(t_data) * parser->comm[i].dt_nb);
        fill_data(parser->comm[i]);
        i++;
    }

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