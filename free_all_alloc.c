/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_alloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:48:57 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/13 00:43:17 by maddou           ###   ########.fr       */
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
    // while (i < parser->lex->pipe_nb)
    // {
    //     j = 0;
    //     // printf("%d\n", parser->comm[i].dt_nb);
    //     while (parser->comm[i].cmd[j] != NULL)
    //     {
    //         printf ("%s\n", parser->comm[i].cmd[j]);
    //         j++;
    //     }
    //     i++;
    // }
	free_double_array(parser->lex->token);
	while (i < parser->lex->pipe_nb)
	{	
		j = 0;
		free_double_array(parser->comm[i].cmd);
		while (j < parser->comm[i].dt_nb)
		{
			free(parser->comm[i].dt[j].data);
			free(parser->comm[i].dt[j].copy_data);
			j++;
		}
		free(parser->comm[i].dt);
		j = 0;
		while (j < parser->comm[i].nb_red)
		{
			// free(parser->comm[i].red[j].copy_data);
			free(parser->comm[i].red[j].data);
			j++;
		}
		free(parser->comm[i].red);
		free(parser->comm[i].red);
		free_double_array(parser->comm[i].new_cmd);	
		i++;
	}
	
	
}