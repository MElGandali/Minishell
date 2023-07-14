/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:06:35 by maddou            #+#    #+#             */
/*   Updated: 2023/07/13 18:26:32 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*creat_node(char *data)
{
	t_env	*head;

	head = malloc(sizeof(t_env));
	head->all = data;
	head->next = NULL;
	return (head);
}
