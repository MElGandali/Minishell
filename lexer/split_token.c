/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:06:38 by maddou            #+#    #+#             */
/*   Updated: 2023/07/12 15:44:52 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_token(t_lexer *lex)
{
	if (split_spaces(lex) == -1)
		return (-1);
	if (lex->word[0] == NULL)
	{
		free(lex->word[0]);
		return (-1);
	}
	if (redir_pipe_error_one_arg(lex) == -1)
		return (-1);
	if (split_pipe_redir(lex) == -1)
		return (-1);
	if (split_pipe_heredoc(lex) == -1)
		return (-1);
	if (redir_pipe_error_mult_arg(lex) == -1)
		return (-1);
	return (0);
}
