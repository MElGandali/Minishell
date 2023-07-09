/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:54:38 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/09 15:29:05 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void    special_var(char **argv)
{
    int i;

    i = 1;
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
                // free(argv[i]);
                argv[i] = ft_itoa(g_exit);
            }
            i++;
        }
    }
}
