/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:53:39 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/08 20:22:20 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"../minishell.h"

void	cd_command(t_parser *parser, char **argv)
{
    char *homedir;
    int i;

    i = 0;
    homedir = NULL;
    if (argv[1] && ft_strcmp(argv[1], "-") == 0)
    {
        homedir = get_env(parser, "OLDPWD");
        update_env(parser, "OLDPWD");
        if (homedir == NULL)
        {
            printf("bash: cd: OLDPWD not set\n");
            g_exit = 1;
        }
        chdir(homedir);
        update_env(parser, "PWD");
    }
    else if (argv[1] == NULL)
    {
        homedir = get_env(parser, "HOME");
        update_env(parser, "OLDPWD");
        chdir(homedir);
        update_env(parser, "PWD");
    }
    else
    {
        update_env(parser, "OLDPWD");
        if (chdir(argv[1]) != 0)
        {
            printf("bash: cd: %s: %s\n",argv[1], strerror(errno));
            g_exit = 1;
        }
        else
        {
          homedir = ft_substr(argv[1], 0, ft_strlen(argv[1]));
          update_env(parser, "PWD");
        }
    }
}
