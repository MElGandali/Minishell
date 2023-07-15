/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:34:19 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/15 00:11:44 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_exist_key(t_env *exn, char *key)
{
	t_env	*tmp;

	tmp = exn;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	check_valid_key(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '_' && ft_isalpha(str[i]) == 0)
		return (1);
	i++;
	while (str[i] != '=' && str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	find_end_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	return (i);
}

int	existing_key(t_env *exn, char *str)
{
	t_env	*tmp1;
	char	*key;

	tmp1 = exn;
	key = ft_substr(str, 0, find_end_key(str));
	while (tmp1)
	{
		if (ft_strcmp(tmp1->key, key) == 0)
		{
			free(key);
			return (1);
		}
		tmp1 = tmp1->next;
	}
	free(key);
	return (0);
}
