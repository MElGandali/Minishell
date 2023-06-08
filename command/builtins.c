/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 23:07:52 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/08 16:18:31 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void builtin_commands(char **argv)
{
    if (ft_strnstr(argv[0], "echo") == 0)
        echo_command(argv);
    else if (ft_strnstr(argv[0], "cd") == 0)
        cd_command(argv);
    else if (ft_strnstr(argv[0], "pwd") == 0)
        pwd_command(argv);
    // else if (ft_strnstr(comm->cmd[0], "export") == 0)
    //     export_command(comm);
    // else if (ft_strnstr(comm->cmd[0], "unset") == 0)
    //     unset_command(comm);
    // else if (ft_strnstr(comm->cmd[0], "env") == 0)
    //     env_command(comm);
    else if (ft_strnstr(argv[0], "exit") == 0)
        exit_command(argv);
}