/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:03:27 by maddou            #+#    #+#             */
/*   Updated: 2023/06/01 16:26:42 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int find_ed (char *env, int i)
{
    while (env[i] != '\0')
    {
        if (env[i] == '=')
            break;
        if (env[i + 1] == '\0')
            break;
        i++;
    }
    return (i);
}

void    fill_dt_utils(char *env, t_env *tmp1, t_env *tmp2)
{
    int i;
    int j;
    (void)tmp1;

    i = 0;
    while (env[i] != '\0')
    {
        j = i;
        i = find_ed(env, i);
        if (env[i] == '=')
        {
            tmp1->key = ft_substr(env, j, i - j);
            tmp2->key = ft_substr(env, j, i - j);
        }
        if (env[i + 1] == '\0')
        {
            tmp1->value = ft_substr(env, j, (i + 1) - j);
            tmp2->value = ft_substr(env, j, (i + 1) - j);
        }
        i++;
    }
}

void fill_dt(char *env, t_env *ev, t_env *ex)
{
    t_env *tmp1;
    t_env *tmp2;

    tmp1 = ev;
    tmp2 = ex;
    while (tmp1->next != NULL && tmp2->next != NULL)
    {
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
    tmp1->all = ft_substr(env, 0, ft_strlen(env));
    tmp2->all = ft_substr(env, 0, ft_strlen(env));
    tmp2->all = ft_strjoin("declare -x ", tmp2->all);
    fill_dt_utils(env, tmp1, tmp2);
}

void creating_new_env(t_lexer *lex, char **env)
{
    int i;

    i = 0;
    lex->env = creat_node(lex->env);
    lex->exp = creat_node(lex->exp);
    while (env[i] != NULL)
    {
        fill_dt(env[i], lex->env, lex->exp);
        add_node(lex->env);
        i++;
    }
}