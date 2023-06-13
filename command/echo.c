/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:59:20 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/13 21:06:13 by mel-gand         ###   ########.fr       */
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
int    echo_command(char **argv)
{
    int i;
    
    i = 1;
    if (argv[1] == NULL)
        printf("\n");
    else   
    {
        while (argv[i] && detect_flag(argv, i) == 1)
            i++;
        while (argv[i])
        {
            printf("%s", argv[i]);
            if (argv[i + 1])
                printf(" ");
            i++;
        }
        if (detect_flag(argv, 1) == 0)
            printf("\n");
    }
    return (0);
}

