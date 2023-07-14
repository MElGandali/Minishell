/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:09:23 by maddou            #+#    #+#             */
/*   Updated: 2023/07/14 19:52:12 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_var(t_var *var, t_env **head)
{
	var->tmp = *head;
	var->prev = NULL;
}

void	remove_node_utils(t_var *var, t_env **head)
{
	if (var->prev)
		var->prev->next = var->tmp->next;
	else
		*head = var->tmp->next;
	var->free_node = var->tmp;
	if (var->tmp->key != NULL)
	{
		free(var->tmp->key);
		var->tmp->key = NULL;
	}
	if (var->tmp->value != NULL)
	{
		free(var->tmp->value);
		var->tmp->value = NULL;
	}
	if (var->tmp->all != NULL)
	{
		free(var->tmp->all);
		var->tmp->all = NULL;
	}
	var->tmp = var->tmp->next;
	free(var->free_node);
}

void	remove_node(t_env **head, char *id)
{
	t_var	var;

	var.tmp = *head;
	var.prev = NULL;
	while (var.tmp)
	{
		if (ft_strcmp(var.tmp->key, id) == 0)
			remove_node_utils(&var, head);
		else
		{
			var.prev = var.tmp;
			var.tmp = var.tmp->next;
		}
	}
}
