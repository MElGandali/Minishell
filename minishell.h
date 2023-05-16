/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:12:52 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/16 23:26:56 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <readline/history.h>
#include<readline/readline.h>
#include<string.h>
#include<signal.h>
#include"libf/libft.h"

// typedef struct  s_token
// {
//     char *word;
//     char *enumerate;
//     int free;
//     struct s_token *next;
//     int index;    
// }   t_token;

typedef struct s_lexer
{
    int i;
    int j;
    int start;
    int end;
    char **word;
    char **token;
    char **enumerate;
    int word_nb;
    int copie_wnb;
    char *line;
}           t_lexer;

int tokenizer(t_lexer *lex);
int check_unclosed_quotes(char *str);
int skip_quote(char *line, int i);


//------------split token---------//
int  split_token(t_lexer *lex);
void split_spaces(t_lexer *lex);
int split_pipe_redir(t_lexer *lex);
int find_end_utils(t_lexer *lex);
int split_quotes(char *line, int i);
void define_word_token(t_lexer *lex);

//--------------error------------//
int quotes_error(t_lexer *lex);
int pipe_error(t_lexer *lex);
int redir_pipe_error(t_lexer *lex);
int tokenizer_error(t_lexer *lex);
#endif