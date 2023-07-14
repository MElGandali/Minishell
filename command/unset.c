/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:23:31 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/14 16:24:12 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_cmd_utils(t_parser *parser, int u, int v)
{
	int	i;
	int	j;

	i = length(parser->lex->env);
	j = length(parser->lex->exp);
	if (i != 0)
		remove_node(&parser->lex->env, parser->comm[u].new_cmd[v]);
	if (j != 0)
		remove_node(&parser->lex->exp, parser->comm[u].new_cmd[v]);
	g_exit = 0;
}

void	unset_command(t_parser *parser)
{
	int	i;
	int	j;
	int	u;
	int	v;

	if (parser->comm[0].new_cmd[1] != NULL)
	{
		u = 0;
		v = 1;
		while (parser->comm[u].new_cmd[v] != NULL)
		{
			if (check_valid_key(parser->comm[u].new_cmd[v]) == 0)
				unset_cmd_utils(parser, u, v);
			else
			{
				g_exit = 1;
				ft_printf("bash: unset: `%s': not a valid identifier\n",
					parser->comm[u].new_cmd[v]);
			}
			v++;
		}
	}
}
