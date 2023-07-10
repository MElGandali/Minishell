/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:39:18 by maddou            #+#    #+#             */
/*   Updated: 2023/07/10 14:42:44 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"


// hna SGV 
int   find_end (char **str, int i)
{
    while (str[i] != NULL)
    {
        if (ft_strcmp(str[i], "|") == 0) 
            break;
        i++;
    }
    return (i);
}
//<< qwd |qwd 'qwd'"ls"| add'da' qwd"re" > fileu'qwd'
void fill_command_utils(t_parser *parser, int end, int start, int c)
{
    int i;

    i = 0;
    parser->comm[c].dt_nb = end - start;
    parser->comm[c].cmd = (char **)malloc(sizeof(char *) * (parser->comm[c].dt_nb + 1));
    while (i < parser->comm[c].dt_nb && parser->lex->token[start] != NULL)
    {
        parser->comm[c].cmd[i] = ft_substr(parser->lex->token[start], 0, ft_strlen(parser->lex->token[start]));
        i++;
        start++;
    }
    parser->comm[c].cmd[i] = NULL;
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
        fill_command_utils(parser, end, start, c);
        parser->comm[c].nb_cmd = 0;
        end++;
        c++;
    }
    /*********************print_comand********************/
    
    // int i = 0;
    // int j = 0;
    // while (i < parser->lex->pipe_nb)
    // {
    //     j = 0;
    //     ft_printf("%d\n", parser->comm[i].dt_nb);
    //     while (parser->comm[i].cmd[j] != NULL)
    //     {
    //         ft_printf ("%s\n", parser->comm[i].cmd[j]);
    //         j++;
    //     }
    //     i++;
    // }
    
    /*********************print_comand********************/
}