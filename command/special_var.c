/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:54:38 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/23 16:49:49 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    special_var(char **argv)
{
    int i;

    i = 1;
    if (ft_strnstr(argv[0], "$?") == 0)
    {
        printf("bash: %d: command not found\n", g_exit);
        return (g_exit = 127);
    }
    else 
    {
        while (argv[i])
        {
            if (ft_strnstr(argv[i], "$?") == 0)
            {
            printf("%d\n", g_exit);
                // free(argv[i]);
                argv[i] = ft_itoa(g_exit);
            }
            i++;
        }
    }
    return (0);
}
