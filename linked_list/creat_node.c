/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:06:35 by maddou            #+#    #+#             */
/*   Updated: 2023/06/06 10:40:55 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *creat_node(char *data)
{
    t_env *head;

    head = malloc(sizeof(t_env));
    head->all = data;
    head->next = NULL;
    return (head);
}