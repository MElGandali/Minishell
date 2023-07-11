/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_alloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:48:57 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/10 16:40:38 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_double_array(char **str)
{
    int i;
    
    i = 0;
	while(str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free (str);
}

void free_parser(t_parser *parser)
{
	int i;
	int j;

	i = 0;
    j = 0;
	while (i < parser->lex->pipe_nb)
    {
        free_double_array(parser->comm[i].cmd);
        j = 0;
        while(j < parser->comm[i].dt_nb)
        {
            free(parser->comm[i].dt[j].data);
            free(parser->comm[i].dt[j].copy_data);
            j++;
        }
        free(parser->comm[i].dt);
        i++;
    }
    free(parser->comm);
}