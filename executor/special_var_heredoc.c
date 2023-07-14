/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_var_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:20:54 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/14 17:45:04 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_special_variable(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '$' && input[i + 1] == '?')
			return (1);
		i++;
	}
	return (0);
}

char	*special_var_her_utils(char *newarg, char *input, int *i, int *k)
{
	if (input[*i] == '$' && input[*i + 1] == '?')
	{
		newarg = copy(newarg, ft_itoa(g_exit), k);
		(*i)++;
	}
	else
		newarg[*k] = input[*i];
	(*k)++;
	return (newarg);
}

char	*special_var_in_heredoc(char *input)
{
	char	*newarg;
	int		arg_size;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (check_special_variable(input) == 1)
	{
		arg_size = alloc_newarg(input);
		newarg = ft_calloc(arg_size + 1, 1);
		while (input[i])
		{
			newarg = special_var_her_utils(newarg, input, &i, &k);
			i++;
		}
		newarg[k] = '\0';
		free(input);
	}
	else
		return (input);
	return (newarg);
}
