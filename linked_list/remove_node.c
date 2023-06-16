/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:09:23 by maddou            #+#    #+#             */
/*   Updated: 2023/06/15 23:17:27 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void ft_var(t_var *var, t_env **head)
{
    var->tmp = *head;
    // varfree_node;
    var->prev = NULL;
}

//t_env *remove_node(t_env **head, char *id)
void remove_node(t_env **head, char *id)
{
    t_var var;
   
    var.tmp = *head;
    var.prev = NULL;
    while (var.tmp)
    {
        if (ft_strcmp(var.tmp->key , id) == 0)
        {
            if (var.prev)
                var.prev->next = var.tmp->next;
            else
                *head = var.tmp->next;
            var.free_node = var.tmp;
            if (var.tmp->key != NULL)
                free(var.tmp->key);
            if (var.tmp->value != NULL)
                free(var.tmp->value);
            free(var.tmp->all);
            var.tmp = var.tmp->next;
            free(var.free_node);
        }
        else
        {
            var.prev = var.tmp;
            var.tmp = var.tmp->next;
        }
    }
    // printf ("%s", head->all);
    // return (*head);
}