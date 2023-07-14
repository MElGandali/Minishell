/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 23:02:18 by maddou            #+#    #+#             */
/*   Updated: 2023/07/13 18:25:11 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_node(t_env *node, t_env **head)
{
	t_env	*tmp;

	tmp = *head;
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp)
		tmp->next = node;
	else
		*head = node;
}
