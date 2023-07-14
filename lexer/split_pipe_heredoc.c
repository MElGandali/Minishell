/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:14:32 by maddou            #+#    #+#             */
/*   Updated: 2023/07/12 20:07:07 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	countntoken(char **token, int cur_wnb)
{
	int	nb;
	int	i;

	i = 0;
	nb = cur_wnb;
	while (token[i] != NULL)
	{
		if (ft_strcmp(token[i], "|<<") == 0)
			nb++;
		i++;
	}
	return (nb);
}

char	**split_pip_her(t_lexer *lex, char **new_token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (lex->token[i] != NULL)
	{
		if (ft_strcmp(lex->token[i], "|<<") == 0)
		{
			new_token[j++] = ft_strdup("|");
			new_token[j] = ft_strdup("<<");
		}
		else
			new_token[j] = ft_strdup(lex->token[i]);
		j++;
		i++;
	}
	new_token[j] = NULL;
	free_double_array(lex->token);
	lex->token = new_token;
	return (new_token);
}

int	split_pipe_heredoc(t_lexer *lex)
{
	char	**new_token;
	int		nb;

	nb = countntoken(lex->token, lex->curr_wnb);
	new_token = NULL;
	if (nb > lex->curr_wnb)
	{
		lex->curr_wnb = nb;
		new_token = malloc(sizeof(char *) * (nb + 1));
		if (!new_token)
			return (-1);
		new_token = split_pip_her(lex, new_token);
	}
	return (0);
}
