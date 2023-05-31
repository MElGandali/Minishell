/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 23:02:18 by maddou            #+#    #+#             */
/*   Updated: 2023/05/31 23:03:02 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *add_node(t_env *head)
{
    t_env *tmp = head;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = malloc(sizeof(t_env));
    tmp->next->next = NULL;
    return (head);
}