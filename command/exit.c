/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:16:16 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/08 16:10:03 by mel-gand         ###   ########.fr       */
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
        exit(0);
    while (argv[1][i])
    {
        if (ft_isalpha(argv[1][i]) != 0)
        {
            ch = 1;
            break;
        }
        i++;
    }
    if (ch == 1 || (ft_atoi(argv[1]) > LONG_LONG_MAX && argv[1][0] != '-')  /*|| ft_atoi(argv[1]) < LONG_LONG_MIN*/)
    {
        printf("exit\nbash: exit: %s: numeric argument required", argv[1]);
        exit(255);
    }
    if (argv[2])
        printf("exit\nbash: exit: too many arguments");
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
    exit (status);
}

