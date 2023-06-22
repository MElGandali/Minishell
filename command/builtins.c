/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 23:07:52 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/19 20:24:43 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int builtin_commands(t_parser *parser)
{
    // printf ("%s\n", parser->lex->env->all);
    if (ft_strnstr(parser->comm->new_cmd[0], "echo") == 0)
        g_exit = echo_command(parser->comm->new_cmd);
    else if (ft_strnstr(parser->comm->new_cmd[0], "cd") == 0)
        g_exit = cd_command(parser->comm->new_cmd);
    else if (ft_strnstr(parser->comm->new_cmd[0], "pwd") == 0)
        g_exit = pwd_command();
    else if (ft_strnstr(parser->comm->new_cmd[0], "$?") == 0)
        g_exit = special_var(parser->comm->new_cmd);
    else if (ft_strcmp(parser->comm->cmd[0], "export") == 0)
        export_command(parser, 0);
    else if (ft_strnstr(parser->comm->cmd[0], "unset") == 0)
        unset_command(parser);
    else if (ft_strnstr(parser->comm->new_cmd[0], "env") == 0)
        env_command(parser, 0);
    else if (ft_strnstr(parser->comm->new_cmd[0], "exit") == 0)
        exit_command(parser->comm->new_cmd);
    return (g_exit);
}