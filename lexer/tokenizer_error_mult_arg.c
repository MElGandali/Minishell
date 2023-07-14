/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_error_mult_arg.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:48:10 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/12 15:23:41 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_syntax_error(t_lexer *lex, int i)
{
	if ((ft_strnstr(lex->token[i], "|") == 0
			|| ft_strnstr(lex->token[i], ">") == 0
			|| ft_strnstr(lex->token[i], "<") == 0)
		&& (ft_strnstr(lex->token[i + 1], "|") == 0
			|| ft_strnstr(lex->token[i + 1], ">") == 0
			|| (ft_strnstr(lex->token[i + 1], "<") == 0
				&& ft_strlen(lex->token[i + 1]) == 1)))
	{
		free_double_array(lex->token);
		ft_putstr_fd("bash: syntax error\n", 2);
		g_exit = 258;
		return (-1);
	}
	return (0);
}

int	redir_pipe_error_mult_arg(t_lexer *lex)
{
	int	i;

	i = 0;
	while (lex->token[i])
	{
		if (check_syntax_error(lex, i) == -1)
			return (-1);
		if (ft_strnstr(lex->token[0], "|") == 0
			|| ft_strnstr(lex->token[lex->curr_wnb - 1], "|") == 0
			|| ft_strnstr(lex->token[lex->curr_wnb - 1], "<") == 0
			|| ft_strnstr(lex->token[lex->curr_wnb - 1], ">") == 0)
		{
			free_double_array(lex->token);
			ft_putstr_fd("bash: syntax error\n", 2);
			g_exit = 2;
			return (-1);
		}
		i++;
	}
	return (0);
}
