/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:17:55 by maddou            #+#    #+#             */
/*   Updated: 2023/07/14 23:39:30 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_export(t_env *exp)
{
	if (check_dataenvexp(exp->all) == 0)
		ft_printf("declare -x %s\n", exp->all);
	else if (check_dataenvexp(exp->all) == 1 && exp->value != NULL)
		ft_printf("declare -x %s=\"%s\"\n", exp->key, exp->value);
	else if (check_dataenvexp(exp->all) == 1 && exp->value == NULL)
		ft_printf("declare -x %s=\"\"\n", exp->key);
}

void	add_new_value(t_parser *parser, int i, int j)
{
	if (check_dataenvexp(parser->comm[i].new_cmd[j]) == 1)
		creat_add_node(parser, i, j, 'e');
	else
		creat_add_node(parser, i, j, 'x');
}

void	export_command_utils(t_parser *parser, t_env *exp, int i, int j)
{
	if (check_valid_key(parser->comm[i].new_cmd[j]) == 0)
	{
		if (existing_key(parser->lex->exp, parser->comm[i].new_cmd[j]) == 1)
			remove_and_replace_value(parser, exp, i, j);
		else
			add_new_value(parser, i, j);
		free_double_array(parser->lex->ar_env);
		ft_tran_env(parser->lex);
		g_exit = 0;
	}
	else
	{
		g_exit = 1;
		ft_printf("bash: export: `%s': not a valid identifier\n",
			parser->comm[i].new_cmd[j]);
	}
}

void	export_command(t_parser *parser, int i)
{
	t_env	*exp;
	t_env	*env;
	int		j;

	exp = parser->lex->exp;
	env = parser->lex->env;
	j = 1;
	if (parser->comm[i].new_cmd[1] == NULL)
	{
		while (exp)
		{
			print_export(exp);
			exp = exp->next;
		}
		g_exit = 0;
	}
	else
	{
		while (parser->comm[i].new_cmd[j] != NULL)
		{
			export_command_utils(parser, exp, i, j);
			j++;
		}
	}
}
