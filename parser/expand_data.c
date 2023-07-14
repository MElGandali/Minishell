/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:00:44 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/13 15:10:32 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_exit(t_env *env, char *envmnt, char **new_data)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 0;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, envmnt) == 0)
		{
			while (tmp->value != NULL && tmp->value[i] != '\0')
			{
				*new_data = ft_copier(tmp->value[i], *new_data);
				i++;
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	expand_data(t_env *env, char *data, int *j, char **new_data)
{
	int		i;
	char	*envmnt;

	i = *j + 1;
	envmnt = NULL;
	while (data[i] != '\0')
	{
		if (data[i] == '_' || ft_isalnum(data[i]) == 1)
			envmnt = ft_copier(data[i], envmnt);
		else
			break ;
		i++;
	}
	if (envmnt != NULL)
		check_exit(env, envmnt, new_data);
	*j = --i;
	free(envmnt);
}
