/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 23:07:52 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/11 23:29:18 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"
#include <unistd.h>

void    update_env(t_parser *parser, char *var)
{
    t_env *env;
    t_env *exp;
    
    env = parser->lex->env;
    exp = parser->lex->exp;
    while (env)
    {
        if (ft_strcmp(env->key, var) == 0)
        {
            free(env->value);
            env->value = NULL;
            env->value = getcwd(env->value , sizeof(env->value));
            free(env->all);
            env->all = NULL;
            env->all = ft_strjoin(env->all, env->key);
            env->all = ft_strjoin(env->all, "=");
            env->all = ft_strjoin(env->all, env->value);
        }
        env = env->next;
    }
    while (exp)
    {
        if (ft_strcmp(exp->key, var) == 0)
        {
            free(exp->value);
            exp->value = NULL;
            exp->value = getcwd(exp->value , sizeof(exp->value));
            free(exp->all);
            exp->all = NULL;
            exp->all = ft_strjoin(exp->all, exp->key);
            exp->all = ft_strjoin(exp->all, "=");
            exp->all = ft_strjoin(exp->all, exp->value); 
        }
        exp = exp->next;
    }
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
    return (NULL);
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
        exit_command(parser, parser->comm->new_cmd);
}