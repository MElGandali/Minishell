/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:12:52 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/13 16:50:54 by maddou           ###   ########.fr       */
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

typedef struct  s_token
{
    char *word;
    char *enumerate;
    int index;    
}   t_token;

typedef struct s_lexer
{
    int i;
    int j;
    int start;
    int end;
    char **lexer;
    char **word;
    char **token;
    int token_nb;
    t_token  *tkn;
    char **enumerate;
    int word_nb;
    char *line;
}           t_lexer;

int tokenizer(t_lexer *lex);
int check_unclosed_quotes(char *str);
int skip_quote(char *line, int i);


//------------split token---------//
int  split_token(t_lexer *lex);
char **split_spaces(t_lexer *lex);
char **split_pipe_redir(t_lexer *lex);
int find_end_utils(t_lexer *lex);
int split_quotes(char *line, int i);
void define_word_token(t_lexer *lex);

//--------------error------------//
int quotes_error(t_lexer *lex);
int pipe_error(t_lexer *lex);
int redir_pipe_error(t_lexer *lex);
int tokenizer_error(t_lexer *lex);
#endif