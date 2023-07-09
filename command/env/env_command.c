/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:58:16 by maddou            #+#    #+#             */
/*   Updated: 2023/07/09 15:29:05 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void env_command(t_parser *parser, int i)
{
    t_env *tmp1;

    tmp1 = parser->lex->env;
    if (parser->comm[i].new_cmd[1] == NULL)
    {
        while (tmp1)
        {
            ft_printf ("%s\n", tmp1->all);
            tmp1 = tmp1->next;
        }
    }
}