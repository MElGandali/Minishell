/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:40:13 by maddou            #+#    #+#             */
/*   Updated: 2023/05/31 22:08:58 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

t_env *creat_list(int nb)
{
    t_env *head = malloc(sizeof(t_env));
    t_env *list = head;
    int i = 1;
    
    while(i < nb)
    {
        list->next = malloc(sizeof (t_env));
        list = list->next;
        i++;
    }
    list->next = NULL;
    return (head);
}
