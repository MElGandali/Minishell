/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 23:02:18 by maddou            #+#    #+#             */
/*   Updated: 2023/06/06 10:40:37 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void add_node(t_env *node,t_env **head)
{
    t_env *tmp = *head;
    
    while (tmp && tmp->next != NULL)
        tmp = tmp->next;
    if(tmp)
        tmp->next = node;
    else
        *head = node;
}