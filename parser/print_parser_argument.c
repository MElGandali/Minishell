/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parser_argument.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:23:55 by maddou            #+#    #+#             */
/*   Updated: 2023/07/09 15:29:05 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print(t_parser *parser, int nb_red, int nb_newcmd, int i)
{
    int x;

    x = 0;
    ft_printf ("command number %d\n", i);
        if (nb_red != 0)
        {
            ft_printf ("/***********redurection******/\n");
            if (x < nb_red)
            {
                while (x < nb_red)
                {
                    ft_printf ("name est           :%d\n", parser->comm[i].red[x].name);
                    ft_printf ("ex_dollal est      :%d\n", parser->comm[i].red[x].ex_dollar);
                    ft_printf ("copy data est      :%s\n", parser->comm[i].red[x].copy_data);
                    ft_printf ("data est           :%s\n", parser->comm[i].red[x].data);
                    x++;
                    ft_printf ("/********file || delimiter***********/\n");
                    ft_printf ("name est           :%d\n", parser->comm[i].red[x].name);
                    ft_printf ("ex_dollal est      :%d\n", parser->comm[i].red[x].ex_dollar);
                    ft_printf ("copy data est      :%s\n", parser->comm[i].red[x].copy_data);
                    ft_printf ("data est           :%s\n", parser->comm[i].red[x].data);
                    ft_printf ("%d\n", x);
                    x++;
                }
            }
            else   
                ft_printf ("NOTHING THE REDURECT\n");
            ft_printf ("/***********redurection******/\n");
        }
        x = 0;
        if (nb_newcmd  != 0)
        {
            ft_printf ("/*************argument***************/\n");
            if (parser->comm[i].new_cmd[x] != NULL)
            {
                while (parser->comm[i].new_cmd[x] != NULL)
                {
                    ft_printf ("/-+-+-+-+-+ %s -+-+-+-+-+/\n",parser->comm[i].new_cmd[x]);
                    x++;
                }
                ft_printf ("/*************argument***************/\n");
            }
            else   
                ft_printf ("NOTHING THE ARGUMENT\n");
        }
}