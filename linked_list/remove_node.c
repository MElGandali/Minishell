/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:09:23 by maddou            #+#    #+#             */
/*   Updated: 2023/05/31 22:25:01 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void ft_var(t_var *var, t_env *head)
{
    var->tmp = head;
    // varfree_node;
    var->prev = NULL;
}

t_env *remove_node(t_env *head, char *id)
{
   t_var var;
   
   ft_var(&var, head);
    while (var.tmp)
    {
        if (ft_strcmp(var.tmp->data , id) != 0)
        {
            if (var.prev)
                var.prev->next = var.tmp->next;
            else
                head = var.tmp->next;
            var.free_node = var.tmp;
            free(var.tmp->id);
            free(var.tmp->data);
            var.tmp = var.tmp->next;
            free(var.free_node);
        }
        else
        {
            var.prev = var.tmp;
            var.tmp = var.tmp->next;
        }
    }
    return (head);
}