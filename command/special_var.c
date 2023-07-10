/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:54:38 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/10 12:20:06 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void    special_var(char **argv)
{
    int i;
    char *newarg;
    int j;
    
    i = 1;
    j = 0;
    newarg = NULL;
    if (ft_strnstr(argv[0], "$?") == 0)
    {
        ft_printf("bash: %d: command not found\n", g_exit);
        g_exit = 127;
    }
    else 
    {
        while (argv[i])
        {
            if (ft_strnstr(argv[i], "$?") == 0)
            {
                while (argv[i][j])
                {
                    
                    if (argv[i][j] == '$' && argv[i][j + 1] == '?')
                    {
                        printf("ok\n");
                        newarg = ft_strjoin(newarg, ft_itoa(g_exit));
                        printf("%s\n", newarg);
                        j++;
                    }
                    newarg[j] = argv[i][j];
                    j++;
                }
            }
            i++;
        }
    }
}
