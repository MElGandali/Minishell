/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:39:18 by maddou            #+#    #+#             */
/*   Updated: 2023/05/23 13:26:56 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int   find_end (char **str, int i)
{
    while (str[i] != NULL)
    {
        if (ft_strnstr(str[i], "|") == 0 && ft_strlen(str[i]) <= 1)
            break;
        i++;
    }
    return (i);
}

char    **fill_command_utils(t_parser *parser,char **cmd, int end, int start)
{
    int i;
    int diff;

    i = 0;
    diff = end - start;
    cmd = (char **)malloc(sizeof(char *) * (diff + 1));
    while (i < diff)
    {
        cmd[i] = ft_substr(parser->lex->token[start], 0, ft_strlen(parser->lex->token[start]));
        i++;
        start++;
    }
    cmd[i] = NULL;
    return(cmd);
}

void    fill_command (t_parser *parser)
{
    int end;
    int start;
    int c;

    end = 0;
    start = 0;
    c = 0;
    while (c < parser->lex->pipe_nb)
    {
        start = end;
        end = find_end (parser->lex->token, end);
        parser->comm[c].cmd = fill_command_utils(parser,parser->comm[c].cmd, end, start);
        c++;
        end++;
    }
    
    int i = 0;
    int j = 0;
    while (i < parser->lex->pipe_nb)
    {
        j = 0;
        while (parser->comm[i].cmd[j] != NULL)
        {
            printf("%s\n", parser->comm[i].cmd[j]);
            j++;
        }
        i++;
    }
}