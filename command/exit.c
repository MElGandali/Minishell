/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:16:16 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/09 17:17:24 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void    exit_cases(char **argv)
{
    int i;
    int ch;

    i = 0;
    ch = 0;
    if (argv[1] == NULL)
        exit(g_exit);
    while (argv[1][i])
    {
        if (ft_isalpha(argv[1][i]) != 0)
        {
            ch = 1;
            break;
        }
        i++;
    }
    if (ch == 1 || (ft_atoi(argv[1]) > LLONG_MAX && argv[1][0] != '-'))
    {
        ft_printf("bash: exit: %s: numeric argument required\n", argv[1]);
        g_exit = 255;
        exit(255);
    }
    if (argv[2])
    {
        ft_printf("bash: exit: too many arguments\n");
        g_exit = 1;
    }
}

void    exit_command(char **argv)
{
    long long int status;
    int i;
    int ch;
    
    i = 0;
    ch = 0;
    
    exit_cases(argv);
    if (g_exit != 1)
    {    
        status = ft_atoi(argv[1]);
        g_exit = status;
        exit (status);
    }
}
