/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:27:27 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/09 18:28:57 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void dquote(char *str, int *i)
{
    int cnt;
    int x;
    x = 0;

    cnt = 0;
    while (str[*i])
    {
        if (str[*i] == 34)
        {
            cnt++;
            break;
        }
        (*i)++;
    }
    if (cnt == 0)
    {
        printf("Syntax Error: missing dquote\n");
        free(str);
    }
}

void quote(char *str, int *i)
{
    int cnt;

    cnt = 0;
    while (str[*i])
    {
        if (str[*i] == 39)
        {
            cnt++;
            break;
        }
        (*i)++;
    }
    if (cnt == 0)
    {
        printf("Syntax Error: missing squote\n");
        free(str);
    }
}

void handle_quotes(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (str[i] == 34)
		{
			i++;
            dquote(str,&i);
		}
        else if (str[i] == 39)
		{
			i++;
            quote(str,&i);
		}
    i++;
    }
}
