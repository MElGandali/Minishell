/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parser_argument.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:23:55 by maddou            #+#    #+#             */
/*   Updated: 2023/06/12 16:26:13 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print(t_parser *parser, int nb_red, int nb_newcmd, int i)
{
    int x;

    x = 0;
    printf ("command number %d\n", i);
        if (nb_red != 0)
        {
            printf ("/***********redurection******/\n");
            if (x < nb_red)
            {
                while (x < nb_red)
                {
                    printf ("name est           :%d\n", parser->comm[i].red[x].name);
                    printf ("ex_dollal est      :%d\n", parser->comm[i].red[x].ex_dollar);
                    printf ("copy data est      :%s\n", parser->comm[i].red[x].copy_data);
                    printf ("data est           :%s\n", parser->comm[i].red[x].data);
                    x++;
                    printf ("/********file || delimiter***********/\n");
                    printf ("name est           :%d\n", parser->comm[i].red[x].name);
                    printf ("ex_dollal est      :%d\n", parser->comm[i].red[x].ex_dollar);
                    printf ("copy data est      :%s\n", parser->comm[i].red[x].copy_data);
                    printf ("data est           :%s\n", parser->comm[i].red[x].data);
                    printf ("%d\n", x);
                    x++;
                }
            }
            else   
                printf ("NOTHING THE REDURECT\n");
            printf ("/***********redurection******/\n");
        }
        x = 0;
        if (nb_newcmd  != 0)
        {
            printf ("/*************argument***************/\n");
            if (parser->comm[i].new_cmd[x] != NULL)
            {
                while (parser->comm[i].new_cmd[x] != NULL)
                {
                    printf ("/-+-+-+-+-+ %s -+-+-+-+-+/\n",parser->comm[i].new_cmd[x]);
                    x++;
                }
                printf ("/*************argument***************/\n");
            }
            else   
                printf ("NOTHING THE ARGUMENT\n");
        }
}