/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:53:39 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/13 21:16:55 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"../minishell.h"

int	cd_command(char **argv) // still, i need to update $PWD and $OLDPWD
{
    char *homedir;
    int i;

    i = 0;
    if (argv[1] && ft_strcmp(argv[1], "-") == 0)
    {
        homedir = getenv("OLDPWD");
        chdir(homedir);
        return (0);
    }
    if (argv[1] == NULL)
    {
        homedir = getenv("HOME");
        chdir(homedir);
        return (0);
    }
    else
    {
        if ((access(argv[1], 0)== 0))
        {
            if (chdir(argv[1]) != 0)
            {
                printf("bash: cd: %s: %s\n",argv[1], strerror(errno));
                return (1);
            }
        }
        else
        {
            printf("bash: cd: %s: %s\n",argv[1], strerror(errno));
            return (1);
        }
    }
    return (0);
}
