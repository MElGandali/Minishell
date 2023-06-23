/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:53:39 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/23 22:02:18 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"../minishell.h"

void	cd_command(t_parser *parser, char **argv) // still, i need to update $PWD and $OLDPWD
{
    char *homedir;
    int i;

    i = 0;
    
    if (argv[1] && ft_strcmp(argv[1], "-") == 0)
    {
        homedir = get_env(parser, "OLDPWD");
        if (homedir == NULL)
        {
            printf("bash: cd: OLDPWD not set\n");
            g_exit = 1;
        }
        chdir(homedir);
    }
    if (argv[1] == NULL)
    {
        homedir = get_env(parser, "HOME");
        // update_env(parser, "OLDPWD", homedir);
        chdir(homedir);
    }
    else
    {
            if (chdir(argv[1]) != 0)
            {
                printf("bash: cd: %s: %s\n",argv[1], strerror(errno));
                g_exit = 1;
            }
    }
}
