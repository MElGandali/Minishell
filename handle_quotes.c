/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:27:27 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/09 16:10:08 by mel-gand         ###   ########.fr       */
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
        rl_on_new_line();
        //rl_replace_line("",0);
        rl_redisplay();
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
        rl_on_new_line();
        //rl_replace_line("",0);
        rl_redisplay();
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
