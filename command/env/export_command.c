/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:17:55 by maddou            #+#    #+#             */
/*   Updated: 2023/06/13 22:50:51 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void export_command(t_parser *parser, int i)
{
    t_env *exp;
    (void)(i);
     
    exp = parser->lex->exp;
    if (parser->comm[i].new_cmd[1] == NULL)
    {
        while (exp)
        {
            printf ("declare -x %s=\"%s\"\n", exp->key, exp->value);
            exp = exp->next;
        }
    }
}