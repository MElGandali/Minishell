/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:31:38 by maddou            #+#    #+#             */
/*   Updated: 2023/06/22 23:11:44 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_multi_arg(char **redirect)
{
    int i;
    int j;
    char *check_name;
    int check_null;
    int check_char;

    i = 0;
    check_null = 0;
    check_char = 0;
    while (redirect[i] != NULL)
    {
        j = 0;
        check_name = NULL;
        while (redirect[i][j] != '\0')
        {
            if (redirect[i][j] == '\'' || redirect[i][j] == '\"')
                check_name = if_quote_fill(redirect[i], &j, check_name);
            else  
                check_name = ft_copier(redirect[i][j], check_name);
            j++;
        }
        if (check_name != NULL)
            check_char++;
        // else   
        //     check_char++;
        printf ("%d \n", check_char);
        free(check_name);
        i++;
    }
    if (check_char == 0 || check_char > 1)
        return (1);
    return (0);
}
int check_ambiguous(t_red *red)
{
    int i;
    char **check_redirect;
    char *data;
    int check;

    i = 0;
    data = NULL;
    if (red->data == NULL)
        return 1;
    if (red->data[i] == '\0')
        return (1);
    while(red->data[i] != '\0')
    {
        if (red->data[i] == '\"' || red->data[i] == '\'')
            i = skip_quote(red->data, i);
        else if (red->data[i] == ' ' || red->data[i] == '\t' || red->data[i] == '\n')
            red->data[i] = '\n';
        i++;
    }
    check_redirect = ft_split(red->data, '\n', &check);
    if (check == 0)
        return (1);
    else if (check > 1)
    {
        if (check_multi_arg(check_redirect) == 1)
            return (1);
    }
    else if (check == 1)
    {
        i = 0;
        while (check_redirect[0][i] != '\0')
        {
            if (ft_isprint(check_redirect[0][i]) == 1 && check_redirect[0][i] !='\"' 
                && check_redirect[0][i] !='\'' && check_redirect[0][i] !=' ' &&
                check_redirect[0][i] != '\t')
                return (0);
            i++;
        }
        return (1);
    }
    i = 0;
    while (check_redirect[i] != NULL)
    {
        // if (check_redirect[i][0] != '\0')
        data = ft_strjoin(data, check_redirect[i]);
        i++;
    }
    printf ("%s\n", data);
    // free_double_array(check_redirect);
    return (0);
}
int redir_out(t_cmd *cmd, int i)
{
    // int fd;
    (void)i;
    (void)cmd;
    if (check_ambiguous(&cmd->red[i + 1]) == 1)
    {
        printf (" ambiguous redirect\n");
        return (1);
    }
    return (0);
    // fd = open("")
}

int dredir_out(t_cmd *cmd, int i)
{
    // int fd;
    (void)i;
    (void)cmd;
    if (check_ambiguous(&cmd->red[i + 1]) == 1)
    {
        printf (" ambiguous redirect\n");
        return (1);
    }
    return (0);
    // fd = open("")
}

int redir_in(t_cmd *cmd, int i)
{
    // int fd;
    (void)i;
    (void)cmd;
    if (check_ambiguous(&cmd->red[i + 1]) == 1)
    {
        printf (" ambiguous redirect\n");
        return (1);
    }
    return (0);
    // fd = open("")
}
// char *ft_ex_name_file(char *data)
// {
//     char **ex_data;

    
//     return (data);
// }
int check_redirect(t_cmd *cmd)
{
    int i;

    i = 0;
    while (i < cmd->nb_red)
    {
        if (cmd->red[i].name == 4)
        {
            if (redir_in(cmd, i) == 1)    
                return (1);
            i++;
        }
        if (cmd->red[i].name == 5)
        {
            if (redir_out(cmd, i) == 1)
                return (1);
            // cmd->red[i + 1].data = ft_ex_name_file(cmd->red[i + 1].data);
            i++;
        }
        else if (cmd->red[i].name == 7)
        {
            if (dredir_out(cmd, i) == 1)
                return (1);
            
            i++;
        }
        else  
            i++;
        i++;
    }
    return (0);
}