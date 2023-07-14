/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:40:13 by maddou            #+#    #+#             */
/*   Updated: 2023/07/13 18:25:57 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*creat_list(int nb)
{
	t_env	*head;
	t_env	*list;
	int		i;

	head = malloc(sizeof(t_env));
	list = head;
	i = 1;
	while (i < nb)
	{
		list->next = malloc(sizeof(t_env));
		list = list->next;
		i++;
	}
	list->next = NULL;
	return (head);
}
