/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ncmd_red.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:22:55 by maddou            #+#    #+#             */
/*   Updated: 2023/06/06 17:13:39 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int count_red(t_cmd *comm)
{
    int i;
    int nb;
    
    i = 0;
    nb = 0;
    // ft_printf ("x\n");
    // ft_printf ("zzzz %d\n",comm->dt_nb);
    while (i < comm->dt_nb)
    {
        if (comm->dt[i].name == 4 || comm->dt[i].name == 5
            || comm->dt[i].name == 6 || comm->dt[i].name == 7)
            nb++;
        i++;
    }
    return (nb);
}

void fill_red(t_cmd *comm, int nb)
{
    int i;
    int j;
    int x;
    (void)comm;
    (void)nb;

    i = 0;
    j = 0;
    comm->red = malloc(sizeof(t_red) * nb);
    while (i < comm->dt_nb)
    {
        if (comm->dt[i].name == 4 || comm->dt[i].name == 5
            || comm->dt[i].name == 6 || comm->dt[i].name == 7)
        {
            comm->red[j].name = comm->dt[i].name;
            comm->red[j].ex_dollar = comm->dt[i].ex_dollar;
            comm->red[j].copy_data = ft_strdup(comm->dt[i].copy_data);
            comm->red[j++].data = ft_strdup(comm->dt[i++].data);
            comm->red[j].ex_dollar = comm->dt[i].ex_dollar;
            comm->red[j].name = comm->dt[i].name;
            if (comm->dt[i].data != NULL)
            {
                x = 0;
                comm->red[j].data = NULL;
                // if (check_ambiguous(&comm->red[j + 1]) == 1)
                //     comm->red[j].check_amb = 1;
                // else  
                //     comm->red[j].check_amb = 0;
                while (comm->dt[i].data[x] != '\0')
                {
                    if (comm->dt[i].data[x] == '\'' || comm->dt[i].data[x] == '\"')
                       comm->red[j].data = if_quote_fill(comm->dt[i].data, &x, comm->red[j].data);
                    else  
                        comm->red[j].data = ft_copier(comm->dt[i].data[x], comm->red[j].data);
                    x++;
                }
                // comm->red[j].data = ft_strdup(comm->dt[i].data);
            }
            else  
                comm->red[j].data = NULL;
            comm->red[j].copy_data = ft_strdup(comm->dt[i].copy_data);
            j++;     
        }
        i++;
    }
    // j = 0;
    // while (j < nb)
    // {
    //     ft_printf ("%s %s %d %d\n",comm->red[j].data, comm->red[j].copy_data,comm->red[j].name, comm->red[j].ex_dollar);
    //     j++;
    // }
}

int count_newcmd(char *data)
{
    int i;
    int nb;

    i = 0;
    nb = 1;
    while (data[i] != '\0')
    {
        if (data[i] == '\"' || data[i] == '\'')
            i = skip_quote(data, i);
        if (data[i + 1] != '\0' && data[i] <= 32 && i > 0 && data[i - 1] != 32)
            nb++;
        i++;
    }
    // ft_printf ("ooo");
    // ft_printf ("%d", nb);
    return (nb);
}

int check_red(t_cmd *comm, int i)
{
    if (comm->dt[i].name != 4 && comm->dt[i].name != 5
        && comm->dt[i].name != 6 && comm->dt[i].name != 7
        && comm->dt[i].name != 9 && comm->dt[i].name != 10
        && comm->dt[i].name != 11)
        return (0);
    return (1);
}

// int    newcmd_nb(t_cmd *comm)
// {
//     int i;
//     // int j;
//     int nb;

//     i = 0;
//     nb = 0;
//     while (i < comm->dt_nb)
//     {
//         if (check_red(comm, i) == 0)
//             nb += count_newcmd(comm->dt[i].data);
//         i++;
//     }
//     return (nb);
// }
int ft_check_split(char *data)
{
    int i;

    i = 0;
    while (data[i] != '\0')
    {
        if (data[i] == '\"' || data[i] == '\'')
            i = skip_quote(data, i);
        if (data[i] <= 32)
            return 1;
        i++;
    }
    return (0);
}

char *if_quote_fill(char *data, int *u, char *new_cmd)
{
    char c;
    
    c = data[(*u)];
    (*u)++;
    while (data[*u] != c)
    {
        new_cmd = ft_copier(data[*u], new_cmd);
        (*u)++;
    }
    return (new_cmd);
}

void fill_newcmd (t_cmd *comm, int *j, int i)
{
    int u;
    
    u = 0;
    comm->new_cmd[*j] = NULL;
    while (comm->dt[i].data[u] != '\0')
    {
        if (comm->dt[i].data[u] == '\'' || comm->dt[i].data[u] == '\"')
           comm->new_cmd[*j] = if_quote_fill(comm->dt[i].data, &u, comm->new_cmd[*j]);
        else  
            comm->new_cmd[*j] = ft_copier(comm->dt[i].data[u], comm->new_cmd[*j]);
        u++;
    }
    // ft_printf ("%s\n", comm->new_cmd[*j]);
    (*j)++;    
}

void fill_split_newcmd(t_cmd *comm, int *j, char *data)
{
    int u;

    u = 0;
    comm->new_cmd[*j] = NULL;
    while (data[u] != '\0')
    {
        if (data[u] == '\'' || data[u] == '\"')
           comm->new_cmd[*j] = if_quote_fill(data, &u, comm->new_cmd[*j]);
        else  
            comm->new_cmd[*j] = ft_copier(data[u], comm->new_cmd[*j]);
        u++;
    }
    // ft_printf ("%s\n", comm->new_cmd[*j]);
    (*j)++;
}

void ft_split_data(t_cmd *comm, int i, int *j)
{
    int word_nb;
    char **split_data;
    int c;
    int k;

    c = 0;
    k = 0;
    while (comm->dt[i].data[c] != '\0')
    {
        if (comm->dt[i].data[c] == '\"' || comm->dt[i].data[c] == '\'')
            i = skip_quote(comm->dt[i].data, i);
        else if (comm->dt[i].data[c] == ' ' || comm->dt[i].data[c] == '\t' || comm->dt[i].data[c] == '\n')
            comm->dt[i].data[c] = '\n';
        c++;
    }
    split_data = ft_split(comm->dt[i].data, '\n', &word_nb); 
    while (split_data[k] != NULL)
        fill_split_newcmd(comm, j, split_data[k++]);
}

void check_and_fill_newcmd(t_cmd *comm)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < comm->dt_nb)
    {
        if (check_red(comm, i) == 0)
        {
            if (ft_check_split(comm->dt[i].data) == 1)
                ft_split_data(comm, i ,&j);
            else
                fill_newcmd(comm, &j, i); 
        }
        i++;
    }
    comm->new_cmd[j] = NULL;
}
void fill_newcmd_red(t_parser *parser)
{
    int i;
    int x;
    int j;
    // int nb_red;
    int nb_newcmd;


    i = 0;
    // ft_printf ("%d\n", parser->lex->pipe_nb);
    while (i < parser->lex->pipe_nb)
    {
        x = 0;
        nb_newcmd = 0;
        j = 0;
        parser->comm[i].nb_red = count_red(&parser->comm[i]) * 2;
        // ft_printf ("%d", nb_red);
        if (parser->comm[i].nb_red != 0)
            fill_red(&parser->comm[i], parser->comm[i].nb_red);
        while (j < parser->comm[i].dt_nb)
        {
            if (check_red(&parser->comm[i], j) == 0)
                nb_newcmd += count_newcmd(parser->comm[i].dt[j].data);
            j++;
        }
        // ft_printf ("comand est %d\n", nb_newcmd);
        // ft_printf ("redurection %d\n", nb_red);
        // ft_printf ("*******************\n");
        if (nb_newcmd  != 0)
        {
            parser->comm[i].new_cmd = malloc(sizeof(char *) * (nb_newcmd + 1));
            check_and_fill_newcmd(&parser->comm[i]);
        }
        else   
            parser->comm[i].new_cmd = NULL;
        /**************print****************/
        // ft_printf ("khasha tamsah\n");
        // print(parser, parser->comm[i].nb_red, nb_newcmd, i);
        // exit (0);
        /**************print****************/
        i++;
    }
}