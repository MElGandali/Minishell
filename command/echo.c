/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:59:20 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/09 15:29:05 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int    detect_flag(char **argv, int i)
{
    int j;
    int check;
    
    j = 0;
    check = 0;
    if (argv[i][j] == '-' && argv[i][j + 1] == 'n')
    {
        j++;
        while (argv[i][j])
        {
            if (argv[i][j] != 'n')
            {
                check = 0;
                return (0);
            }
            else if (argv[i][j] == 'n')
                check = 1;
            j++;
        }
        if (check == 1)
            return (1);
    }
    return (check);
}
void   echo_command(char **argv)
{
    int i;
    
    i = 1;
    if (argv[1] == NULL)
        ft_printf("\n");
    else   
    {
        while (argv[i] && detect_flag(argv, i) == 1)
            i++;
        while (argv[i])
        {
            if (ft_strcmp(argv[i], "$?") == 0 && argv[i])
               special_var(argv);
            if (ft_strcmp(argv[i], "$?") != 0)
                ft_printf("%s", argv[i]);
            if (argv[i + 1])
                ft_printf(" ");
            i++;
        }
        g_exit = 0;
        if (detect_flag(argv, 1) == 0)
            ft_printf("\n");
    }
}

