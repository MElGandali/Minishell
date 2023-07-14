/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_rp_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:38:55 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/14 21:32:25 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	protect_malloc(char **ar_env)
{
	if (!ar_env)
		exit (1);
}

int	check_dataenvexp(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	creat_add_node(t_parser *parser, int i, int j, char exv)
{
	t_env			*env;
	t_env			*exp;
	t_var_exp_env	var;

	env = parser->lex->env;
	exp = parser->lex->exp;
	if (exv == 'e')
	{
		var.ev = 'e';
		env = creat_node(ft_strdup(parser->comm[i].new_cmd[j]));
		exp = creat_node(ft_strdup(parser->comm[i].new_cmd[j]));
		fill_dt_utils(parser->comm[i].new_cmd[j], env, exp, &var);
		add_node(env, &parser->lex->env);
		add_node(exp, &parser->lex->exp);
		g_exit = 0;
	}
	else
	{
		var.ev = 'x';
		exp = creat_node(ft_strdup(parser->comm[i].new_cmd[j]));
		fill_dt_utils(parser->comm[i].new_cmd[j], env, exp, &var);
		add_node(exp, &parser->lex->exp);
		g_exit = 0;
	}
}

void	remove_and_replace_value(t_parser *parser, t_env *exp, int i, int j)
{
	char	*key;

	if (check_dataenvexp(parser->comm[i].new_cmd[j]) == 1)
	{
		key = ft_substr(parser->comm[i].new_cmd[j], 0,
				find_end_key(parser->comm[i].new_cmd[j]));
		exp = parser->lex->exp;
		remove_node(&parser->lex->exp, key);
		if (check_exist_key(parser->lex->env, key) == 1)
			remove_node(&parser->lex->env, key);
		free(key);
		creat_add_node(parser, i, j, 'e');
	}
}
