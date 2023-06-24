/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 23:07:52 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/24 21:29:56 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void    update_env(t_parser *parser, char *var, char *dir)
{
    t_env *env;
    t_env *exp;
    
    env = parser->lex->env;
    exp = parser->lex->exp;
    dir = NULL;
    var = NULL;
    while (env)
    {
        if (ft_strcmp(env->key, var) == 0)
        {
            
        }
        env = env->next;
    }
    // while (exp)
    // {
    //     if (ft_strcmp(exp->key, var) == 0)
    //     {
            
    //     }
    //     exp = exp->next;
    // }
}
char    *get_env(t_parser *parser, char *str)
{
    t_env *env;

    env = parser->lex->env;
    while (env)
    {
        if (ft_strcmp(env->key, str) == 0)
            return(env->value);
        env = env->next;
    }
    return (0);
}

void    builtin_commands(t_parser *parser, int i)
{
    if (ft_strnstr(parser->comm[i].new_cmd[0], "echo") == 0)
        echo_command(parser->comm[i].new_cmd);
    else if (ft_strnstr(parser->comm[i].new_cmd[0], "cd") == 0)
        cd_command(parser, parser->comm[i].new_cmd);
    else if (ft_strnstr(parser->comm[i].new_cmd[0], "pwd") == 0)
        pwd_command();
    else if (ft_strnstr(parser->comm[i].new_cmd[0], "$?") == 0)
        special_var(parser->comm[i].new_cmd);
    else if (ft_strcmp(parser->comm[i].cmd[0], "export") == 0)
        export_command(parser, 0);
    else if (ft_strnstr(parser->comm->cmd[0], "unset") == 0)
        unset_command(parser);
    else if (ft_strnstr(parser->comm->new_cmd[0], "env") == 0)
        env_command(parser, 0);
    else if (ft_strnstr(parser->comm->new_cmd[0], "exit") == 0)
        exit_command(parser->comm->new_cmd);
}