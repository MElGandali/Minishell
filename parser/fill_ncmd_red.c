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
            comm->red[j++].data = ft_strdup(comm->dt[i++].data);
            comm->red[j].ex_dollar = comm->dt[i].ex_dollar;
            comm->red[j].name = comm->dt[i].name;
            comm->red[j].data = comm->dt[i].data;
            j++;     
        }
        i++;
    }
    // j = 0;
    // while (j < nb)
    // {
    //     printf ("%s %d %d\n",comm->red[j].data, comm->red[j].name, comm->red[j].ex_dollar);
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
void fill_newcmd (t_cmd *comm, int *j, char **new_cmd, int i)
{
    int u;
    char c;
    
    u = 0;
    (void)new_cmd;
    comm->new_cmd[*j] = NULL;
    while (comm->dt[i].data[u] != '\0')
    {
        printf ("%d", u);
        if (comm->dt[i].data[u] == '\'' || comm->dt[i].data[u] == '\"')
        {
            c = comm->dt[i].data[u++];
            while (comm->dt[i].data[u] != '\0' && comm->dt[i].data[u] != c)
            {
                comm->new_cmd[*j] = ft_copier(comm->dt[i].data[u], comm->new_cmd[*j]);
                u++;
            }
        }
        if (comm->dt[i].data[u + 1] != '\0')
            ft_copier(comm->dt[i].data[u + 1], comm->new_cmd[*j]);
        printf ("%s\n", comm->new_cmd[*j]);
        // printf ("%d", u);
        exit(0);
        u++;
        // if (u == 3)
        //     exit(0);
    }
    (*j)++;    
}
void check_and_fill_newcmd(t_cmd *comm)
{
    int i;
    int j;
    // int check;

    i = 0;
    j = 0;
    while (i < comm->dt_nb)
    {
        if (check_red(comm, i) == 0)
        {
            if (ft_check_split(comm->dt[i].data) == 1)
            {

            }
            else
                fill_newcmd(comm, &j,comm->new_cmd, i);  
        }
        i++;
    }
    // printf ("%s\n", comm->new_cmd[0]);
}
void fill_newcmd_red(t_parser *parser)
{
    int i;
    int j;
    int nb_red;
    int nb_newcmd;


    i = 0;
    while (i < parser->lex->pipe_nb)
    {
        nb_newcmd = 0;
        j = 0;
        nb_red = count_red(&parser->comm[i]) * 2;
        if (nb_red != 0)
            fill_red(&parser->comm[i], nb_red);
        while (j < parser->comm[i].dt_nb)
        {
            if (check_red(&parser->comm[i], j) == 0)
                nb_newcmd += count_newcmd(parser->comm[i].dt[j].data);
            j++;
        }
        // printf ("comand est %d\n", nb_newcmd);
        // printf ("redurection %d\n", nb_red);
        // printf ("*******************\n");
        if (nb_newcmd  != 0)
        {
            parser->comm[i].new_cmd = malloc(sizeof(char *) * (nb_newcmd + 1));
            check_and_fill_newcmd(&parser->comm[i]);
        }
        else   
            parser->comm[i].new_cmd = NULL;
        i++;
    }
}