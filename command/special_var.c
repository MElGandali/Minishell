/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:54:38 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/10 23:21:47 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
#include <stdlib.h>

char *copy(char *newarg, char *g_exit, int *idx)
{
   int i;

   i = 0;
   while (g_exit[i] != '\0')
   {
        newarg[*idx] = g_exit[i];
        (*idx)++;
        i++;
   }
   (*idx)--;
   return (newarg); 
}

int alloc_newarg(char *argv)
{
    int nb_exit;
    int i;
    int j;
    int arg_size;

    i = 0;
    j = 0;
    while (argv[i])
    {
        if (argv[i] == '$' && argv[i + 1] == '?')
        {
            j += 2;
            i++;
        }
        i++;
    }
    nb_exit = ft_strlen(ft_itoa(g_exit));
    arg_size = i - j + (nb_exit * (j / 2));
    return (arg_size);   
}
char    *special_var(char **argv)
{
    int i;
    char *newarg;
    int j;
    int k;
    int arg_size;
    
    i = 1;
    j = 0;
    k = 0;
    arg_size = 0;
    newarg = NULL;
    if (ft_strnstr(argv[0], "$?") == 0)
    {
        g_exit = 2;
        ft_printf("bash: %d: command not found\n", g_exit);
    }
    else 
    {
        while (argv[i])
        {
            if (ft_strnstr(argv[i], "$?") == 0)
            {
                arg_size = alloc_newarg(argv[i]);
                newarg = ft_calloc(arg_size + 1, 1);
                while (argv[i][j])
                { 
                    if (argv[i][j] == '$' && argv[i][j + 1] == '?')
                    {
                        newarg = copy(newarg, ft_itoa(g_exit), &k);
                        j++;
                    }
                    else
                       newarg[k] = argv[i][j]; 
                    j++;
                    k++;
                }
                newarg[k] = '\0';
            }
            i++;
        }
    }
    return (newarg);
}
