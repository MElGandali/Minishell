/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:17:55 by maddou            #+#    #+#             */
/*   Updated: 2023/06/14 22:29:23 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int check_valid_key(char *str)
{
    int i;

    i = 0;
    if (str[i] != '_' && ft_isalpha(str[i]) == 0)
        return (1);
    i++;
    while (str[i] != '=' && str[i] != '\0')
    {
        if (ft_isalnum(str[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}

int check_dataenvexp(char *str)
{
    int i;
    
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

int find_end_key(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '=')
            break;
        i++;
    }
    return (i);
}

int existing_key(t_env *exn, char *str)
{
    t_env *tmp1;
    char *key;

    tmp1 = exn;
    key = ft_substr(str, 0, find_end_key(str));
    while (tmp1)
    {
        if (ft_strcmp(tmp1->key, key) == 0)
        {   
            free(key);
            return (1);
        }
        tmp1 = tmp1->next;
    }
    return (0);
}
void ft_fill_data(t_env *env, t_env *exp, char *id, char *str)
{
    t_env *tmp1;
    t_env *tmp2;

    tmp2 = exp;
    tmp1 = env;
    while (tmp2)
    {
        if (ft_strcmp(tmp2->key, id) == 0)
            break;
    printf ("%s %s\n", id, tmp2->key);
        tmp2 = tmp2->next;
    }
    printf ("%s", tmp2->key);
    // free(id);
    (void)str;
    // free(tmp2->value);
    // free(tmp2->all);
    // free(tmp2->key);
    // tmp2->all = ft_strdup(str);
    // fill_dt_utils(str, tmp1, tmp2, 'v');
}
void export_command(t_parser *parser, int i)
{
    t_env *exp;
    t_env *env;
    char  *key;
    int j;
     
    exp = parser->lex->exp;
    env = parser->lex->env;
    j = 1;
    if (parser->comm[i].new_cmd[1] == NULL)
    {
        while (exp)
        {
            if (check_dataenvexp(exp->all) == 0)
                printf ("declare -x %s\n", exp->all);
            else if (check_dataenvexp(exp->all) == 1 && exp->value != NULL)
                printf ("declare -x %s=\"%s\"\n", exp->key, exp->value);
            else if (check_dataenvexp(exp->all) == 1 && exp->value == NULL)
                printf ("declare -x %s=\"\"\n", exp->key);
            exp = exp->next;
        }
    }
    else    
    {
        while (parser->comm[i].new_cmd[j] != NULL)
        {
            if (check_valid_key(parser->comm[i].new_cmd[j]) == 0)
            {
                if (existing_key(parser->lex->exp, parser->comm[i].new_cmd[j]) == 1)
                {
                    if (check_dataenvexp(parser->comm[i].new_cmd[j]) == 1)
                    {
                        key = ft_substr(parser->comm[i].new_cmd[j], 0, find_end_key(parser->comm[i].new_cmd[j]));
                        // ft_fill_data(parser->lex->exp,parser->lex->env, key, parser->comm[i].new_cmd[j]);
                        // remove_node(parser->lex->exp, key);
                        // free(key);
                        // exp = creat_node(parser->comm[i].new_cmd[j]);
                        // fill_dt_utils(parser->comm[i].new_cmd[j], env, exp, 'x');
                        // add_node(exp, &parser->lex->exp);
                    }
                }
                else   
                {
                    exp = creat_node(parser->comm[i].new_cmd[j]);
                    fill_dt_utils(parser->comm[i].new_cmd[j], env, exp, 'x');
                    add_node(exp, &parser->lex->exp);
                }
            }
            else    
                printf ("bash: export: `%s': not a valid identifier\n", parser->comm[i].new_cmd[j]);
            j++;
        }
    }
    // int k = 0;
    // exp = parser->lex->exp;
    // while (exp)
    // {
    //     printf ("%s\n", )
    //     exp = exp->next;
    // }
}