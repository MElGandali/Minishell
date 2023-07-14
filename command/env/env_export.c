/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:03:27 by maddou            #+#    #+#             */
/*   Updated: 2023/07/14 21:30:57 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_ed(char *env, int i, int check)
{
	while (env[i] != '\0')
	{
		if (env[i] == '=' && check == 0)
			break ;
		i++;
	}
	return (i);
}

void	fill_value_with_null(char *env, t_env *tmp1, t_env *tmp2,
		t_var_exp_env *var)
{
	if ((env[var->i] == '=' && env[var->i + 1] == '\0') || (env[var->i] == '\0'
			&& var->check == 2))
	{
		if (var->ev == 'e')
			tmp1->value = NULL;
		tmp2->value = NULL;
	}
	if (env[var->i] != '\0')
		var->i++;
}

void	fill_dt_utils(char *env, t_env *tmp1, t_env *tmp2, t_var_exp_env *var)
{
	var->check = 0;
	var->i = 0;
	var->j = 0;
	while (env[var->i] != '\0')
	{
		var->j = var->i;
		var->i = find_ed(env, var->i, var->check);
		if (var->check == 0)
		{
			if (var->ev == 'e')
				tmp1->key = ft_substr(env, var->j, var->i - var->j);
			tmp2->key = ft_substr(env, var->j, var->i - var->j);
			if (env[var->i] == '\0')
				var->check = 2;
			else
				var->check++;
		}
		else if (var->check == 1)
		{
			if (var->ev == 'e')
				tmp1->value = ft_substr(env, var->j, (var->i + 1) - var->j);
			tmp2->value = ft_substr(env, var->j, (var->i + 1) - var->j);
		}
		fill_value_with_null(env, tmp1, tmp2, var);
	}
}

void	ft_tran_env(t_lexer *lex)
{
	t_env	*env;
	int		i;
	int		j;

	env = lex->env;
	j = 0;
	i = 0;
	lex->ar_env = NULL;
	if (env != NULL)
	{
		while (env)
		{
			i++;
			env = env->next;
		}
		env = lex->env;
		lex->ar_env = malloc(sizeof(char *) * (i + 1));
		protect_malloc(lex->ar_env);
		while (env)
		{
			lex->ar_env[j++] = ft_strdup(env->all);
			env = env->next;
		}
		lex->ar_env[j] = NULL;
	}
}

void	creating_new_env(t_lexer *lex, char **env)
{
	int				i;
	t_env			*tmp1;
	t_env			*tmp2;
	t_var_exp_env	var;

	i = 0;
	while (env[i] != NULL)
	{
		tmp1 = creat_node(ft_strdup(env[i]));
		tmp2 = creat_node(ft_strdup(env[i]));
		var.ev = 'e';
		fill_dt_utils(env[i], tmp1, tmp2, &var);
		add_node(tmp1, &lex->env);
		add_node(tmp2, &lex->exp);
		i++;
	}
	ft_tran_env(lex);
}
