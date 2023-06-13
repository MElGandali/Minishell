/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:03:27 by maddou            #+#    #+#             */
/*   Updated: 2023/06/13 22:32:39 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

char *add_dquot(char *tmp)
{
    int len;
    char *p;
    int i;
    int j;

    i = 0;
    j = 0;
    len = ft_strlen(tmp) + 3;
    p = malloc(sizeof(char) * len);
    if (!p)
        return 0;
    while (tmp[i] != 0)
    {
        
        p[j] = tmp[i];
        if (tmp[i] == '=')
            p [++j] = '\"';
        j++;
        i++;
    }
    p[j++] = '\"';
    p[j] = '\0';
    free(tmp);
    return (p);
}

// void fill_dt(char *env, t_env *ev, t_env *ex)
// {
//     t_env *tmp1;
//     t_env *tmp2;

//     tmp1 = ev;
//     tmp2 = ex;
//     while (tmp1->next != NULL /*&& tmp2->next != NULL*/)
//     {
//         tmp1 = tmp1->next;
//         // tmp2 = tmp2->next;
//     }
//     tmp1->all = ft_substr(env, 0, ft_strlen(env));
    
//     printf ("%s\n", (ev)->all);
//     // tmp2->all = ft_substr(env, 0, ft_strlen(env));
//     // tmp2->all = add_dquot(tmp2->all);
//     // tmp2->all = ft_strjoin("declare -x ", tmp2->all);
//     // fill_dt_utils(env, tmp1, tmp2);
// }

void creating_new_env(t_lexer *lex, char **env)
{
    int i;
    t_env *tmp1;
    t_env *tmp2;

    lex->env = NULL;
    lex->exp = NULL;
    i = 0;
    while (env[i] != NULL)
    {
        tmp1 = creat_node(ft_strdup(env[i]));
        tmp2 = creat_node(ft_strdup(env[i]));
        fill_dt_utils(env[i], tmp1, tmp2);    
        add_node(tmp1,&lex->env);
        add_node(tmp2,&lex->exp); 
        i++;
    }
    tmp1 = creat_node("x=Hello      ");
    fill_dt_utils("x=Hello      ", tmp1, tmp2);
    add_node(tmp1,&lex->env);
    tmp1 = creat_node("y=      World");
    fill_dt_utils("y=      World", tmp1, tmp2);
    add_node(tmp1,&lex->env);
    // t_env *x = lex->env;
    // printf ("%s", x->all);
    // x = x->next;
    // printf ("%s", x->all);
    // while (x)
    // {
    //     printf ("%s %s %s\n", x->all, x->key, x->value);
    //     x = x->next;
    // }
    // /exit (0);
}