/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:27:27 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/12 16:46:02 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int dquote(char *str, int *i)
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
        return (-1);
    }
    return (0);
}

int quote(char *str, int *i)
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
        return (-1);
    }
    return (0);
}

int  check_unclosed_quotes(char *str)
{
    int     i;
    
    i = 0;
    while (str[i])
    {
        if (str[i] == '\"')
		{
			i++;
            return(dquote(str,&i));
		}
        else if (str[i] == '\'')
		{
			i++;
            return (quote(str,&i));
		}
    i++;
    }
    return (0);
}
