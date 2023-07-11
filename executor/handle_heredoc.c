/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 23:54:32 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/10 22:34:37 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_special_variable(char *input)
{
    int i;

    i = 0;
    while (input[i] != '\0')
    {
        if (input[i] == '$' && input[i + 1] == '?')
            return (1);
        i++;
    }
    return (0);
}
char    *special_var_in_heredoc(char *input)
{
    char *newarg;
    int arg_size;
    int i;
    int k;

    i = 0;
    k = 0;
            if (check_special_variable(input) == 1)
            {
                arg_size = alloc_newarg(input);
                newarg = ft_calloc(arg_size + 1, 1);
                while (input[i])
                { 
                    if (input[i] == '$' && input[i + 1] == '?')
                    {
                        newarg = copy(newarg, ft_itoa(g_exit), &k);
                        i++;
                    }
                    else
                       newarg[k] = input[i]; 
                    k++;
                    i++;
                }
                newarg[k] = '\0';
                free(input);
            }
            else
                return (input);
    return (newarg);
}     
int count_heredoc(t_cmd *comm, int i)
{
    int j;
    int pos;
    j = 0;
    pos = 0;
    while (j < comm[i].nb_red)
    {
        if (comm[i].red->name == 6)
            pos = j;
        j = j + 2;
    }
    return (pos);
}


int here_doc(t_parser *parser, t_red *red)
{
    int i;
    char *input;
    char *save_her;

    i = 0;
    save_her = NULL;
    red->fd = malloc (sizeof(int) * 2 + 1);
    if (pipe(red->fd) == -1)
    {
        perror("pipe");
        exit(2);
    }
    while (1)
    {
        input = readline("> ");
        if (input == NULL || ft_strcmp(input, red->data) == 0)
            break;
        else
        {
            if (red->ex_dollar == 2)
            {
                input = find_dollar_utils(parser, input, 0, 'e');
            if (check_special_variable(input) == 1)
                input = special_var_in_heredoc(input);
            }
            save_her = ft_strjoin(save_her, input);
            save_her = ft_strjoin(save_her, "\n");
            free(input);
        }
    }
    if (save_her != NULL)
        ft_putstr_fd(save_her, red->fd[1]);
    close(red->fd[1]);
    return (red->fd[0]);
}

int    handle_heredoc(t_parser *parser, int i)
{
    int j;
    int fd_r;
    int nb_her;
    
    fd_r = 0;
    nb_her = 0;
    if (parser->comm[i].nb_red != 0)
    {
        j = 0;
        while (j < parser->comm->nb_red)
        {
            if (parser->comm[i].red[j].name == 6)
            {
                // if (j != count_heredoc( parser->comm, i))
                //     close(fd_r);
                fd_r = here_doc(parser, &parser->comm[i].red[j + 1]);
            }    
            j = j + 2;
        }
    }
    return (fd_r);
}