/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:58:16 by maddou            #+#    #+#             */
/*   Updated: 2023/06/15 17:01:07 by maddou           ###   ########.fr       */
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
            printf ("%s\n", tmp1->all);
            tmp1 = tmp1->next;
        }
    }
}