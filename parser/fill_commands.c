/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:39:18 by maddou            #+#    #+#             */
/*   Updated: 2023/06/12 21:44:41 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"


// hna SGV 
int   find_end (char **str, int i)
{
    while (str[i] != NULL)
    {
        if (/*ft_strnstr(str[i], "|") == 0 && ft_strlen(str[i]) <= 1*/ft_strcmp(str[i], "|") == 0) // hna strlen 3lach darnaha
            break;
        i++;
    }
        // printf ("end est %d\n", i);
    return (i);
}
//<< qwd |qwd 'qwd'"ls"| add'da' qwd"re" > fileu'qwd'
void /*char    ***/ fill_command_utils(t_parser *parser/*, char **cmd*/, int end, int start, int c)
{
    int i;

    i = 0;
    parser->comm[c].dt_nb = end - start;
    // printf ("%d %d %d\n", start, end, parser->comm[c].dt_nb);
    parser->comm[c].cmd = (char **)malloc(sizeof(char *) * (parser->comm[c].dt_nb + 1));
    while (i < parser->comm[c].dt_nb && parser->lex->token[start] != NULL)
    {
        parser->comm[c].cmd[i] = ft_substr(parser->lex->token[start], 0, ft_strlen(parser->lex->token[start]));
        // printf ("%d%s\n",i, parser->comm[c].cmd[i]);
        i++;
        start++;
    }
    parser->comm[c].cmd[i] = NULL;
    // return(cmd);
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
        /*parser->comm[c].cmd = */fill_command_utils(parser,/*parser->comm[c].cmd,*/ end, start, c);
        parser->comm[c].nb_cmd = 0;
        // printf ("%d", parser->comm[c].nb_cmd);
        end++;
        c++;
    }
    /*********************print_comand********************/
    
    // int i = 0;
    // int j = 0;
    // while (i < parser->lex->pipe_nb)
    // {
    //     j = 0;
    //     printf("%d\n", parser->comm[i].dt_nb);
    //     while (parser->comm[i].cmd[j] != NULL)
    //     {
    //         printf ("%s\n", parser->comm[i].cmd[j]);
    //         j++;
    //     }
    //     i++;
    // }
    
    /*********************print_comand********************/
}