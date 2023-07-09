/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:03:27 by maddou            #+#    #+#             */
/*   Updated: 2023/07/09 18:07:32 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int find_ed (char *env, int i, int check)
{
    while (env[i] != '\0')
    {
        if (env[i] == '=' && check == 0)
            break;
        // if (env[i + 1] == '\0')
        //     break;
        i++;
    }
    return (i);
}

void    fill_dt_utils(char *env, t_env *tmp1, t_env *tmp2, char ev)
{
    int i;
    int j;
    int check;

    i = 0;
    check = 0;
    while (env[i] != '\0')
    {
        j = i;
        i = find_ed(env, i, check);
        if (check == 0)
        {
            if (ev == 'e')
                tmp1->key = ft_substr(env, j, i - j); 
            tmp2->key = ft_substr(env, j, i - j);
            if (env[i] == '\0')
                check = 2;
            else 
                check++;
        }
        else if (check == 1)
        {
            if (ev == 'e')
                tmp1->value = ft_substr(env, j, (i + 1) - j); 
            tmp2->value = ft_substr(env, j, (i + 1) - j);
        }
        if ((env[i] == '=' && env[i + 1] == '\0') || (env[i] == '\0' && check == 2))
        {
            if (ev == 'e')
                tmp1->value = NULL;
            tmp2->value = NULL;
        }
        if (env[i] != '\0')
            i++;
    }
}

// char *add_dquot(char *tmp)
// {
//     int len;
//     char *p;
//     int i;
//     int j;

//     i = 0;
//     j = 0;
//     len = ft_strlen(tmp) + 3;
//     p = malloc(sizeof(char) * len);
//     if (!p)
//         return 0;
//     while (tmp[i] != 0)
//     {
        
//         p[j] = tmp[i];
//         if (tmp[i] == '=')
//             p [++j] = '\"';
//         j++;
//         i++;
//     }
//     p[j++] = '\"';
//     p[j] = '\0';
//     free(tmp);
//     return (p);
// }

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
    
//     ft_printf ("%s\n", (ev)->all);
//     // tmp2->all = ft_substr(env, 0, ft_strlen(env));
//     // tmp2->all = add_dquot(tmp2->all);
//     // tmp2->all = ft_strjoin("declare -x ", tmp2->all);
//     // fill_dt_utils(env, tmp1, tmp2);
// }

void ft_tran_env(t_lexer *lex)
{
    t_env *env;
    int i;
    int j;

    env = lex->env;
    j = 0;
    i = 0;
    lex->ar_env = NULL;
    if (env != NULL)
    {
        while (env)
        {
            i++;
            env = env->next;
        }  
        env = lex->env;
        lex->ar_env = malloc (sizeof(char *) * (i + 1));
        if (!lex->ar_env)
            exit (1);
        while (env)
        {
            lex->ar_env[j++] = ft_strdup(env->all);
            env = env->next;
        }
        lex->ar_env[j] = NULL;
    }
}

void creating_new_env(t_lexer *lex, char **env)
{
    int i;
    t_env *tmp1;
    t_env *tmp2;

    // lex->env = NULL;
    // lex->exp = NULL;
    i = 0;
    while (env[i] != NULL)
    {
        tmp1 = creat_node(ft_strdup(env[i]));
        tmp2 = creat_node(ft_strdup(env[i]));
        fill_dt_utils(env[i], tmp1, tmp2, 'e');    
        add_node(tmp1,&lex->env);
        add_node(tmp2,&lex->exp); 
        i++;
    }
    ft_tran_env(lex);
    // tmp1 = creat_node("x=");
    // fill_dt_utils("x=", tmp1, tmp2, 'e');
    // add_node(tmp1,&lex->env);
    // tmp2 = creat_node("x=h");
    // fill_dt_utils("x=h", tmp1, tmp2, 'x');
    // add_node(tmp2,&lex->exp);
    // tmp1 = creat_node("y=      World");
    // fill_dt_utils("y=      World", tmp1, tmp2, 'e');
    // add_node(tmp1,&lex->env);
    //  t_env *x = lex->exp;
    // ft_printf ("%s", x->all);
    // x = x->next;
    // ft_printf ("%s", x->all);
    // while (x)
    // {
    //     ft_printf ("declare -x  %s=\"%s\"\n", x->key ,x->value);
    //     x = x->next;
    // }
    //  exit (0);
}