/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:16:16 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/09 15:29:05 by mel-gand         ###   ########.fr       */
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
    {
        g_exit = 1;
        exit(0);
    }
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
        ft_printf("exit\nbash: exit: %s: numeric argument required", argv[1]);
        g_exit = 255;
        exit(255);
    }
    if (argv[2])
    {
        g_exit = 1;
        ft_printf("exit\nbash: exit: too many arguments");
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
    status = ft_atoi(argv[1]);
    g_exit = status;
    exit (status);
}
