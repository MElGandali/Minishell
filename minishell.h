/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:12:52 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/31 23:06:31 by maddou           ###   ########.fr       */
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

typedef struct s_env {
    char *id;
    char *data;
    struct s_env *next;
}   t_env;

typedef struct  s_var
{
    t_env *tmp;
    t_env *free_node;
    t_env *prev;  
}   t_var;

typedef enum e_data
{
    WORD = 1,
    COMMAND,
    FLAG,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	DREDIR_OUT,
	ENV,
    DOC,
    DELIMITER,
}   t_dt;

typedef struct s_lexer
{
    int i;
    int j;
    int start;
    int end;
    char **word;
    char **token;
    int curr_wnb;
    char *line;
    int pipe_nb;
}           t_lexer;

typedef struct s_define_data 
{
    int name;
    t_dt state;
    char *data;
    int position;
    char *name_file;
    char *delimiter;
}   t_data;

typedef struct s_commands
{
    t_env *env;
    t_env *exp;
    char **cmd;
    int dt_nb;
    t_data *dt;
    int i;
}   t_cmd;

typedef struct s_parser
{
    t_cmd *comm;
    t_lexer *lex;
}   t_parser;

//---------free-------//
void free_double_array(char **str);


//------------lexer---------------//

int tokenizer(t_lexer *lex);
int check_unclosed_quotes(char *str);
int skip_quote(char *line, int i);


//------------split token---------//
int  split_token(t_lexer *lex);
int split_spaces(t_lexer *lex);
int split_pipe_redir(t_lexer *lex);
void count_tokens (t_lexer *lex);
// int find_end_utils(t_lexer *lex);
int split_quotes(char *line, int i);
void define_word_token(t_lexer *lex);

//--------------error------------//
int quotes_error(t_lexer *lex);
int pipe_error(t_lexer *lex);
int redir_pipe_error_one_arg(t_lexer *lex);
int redir_pipe_error_mult_arg(t_lexer *lex);
// int tokenizer_error(t_lexer *lex);



//-----------parsing-----------//
int    parser(t_lexer *lex);
void    fill_command (t_parser *parser);
// void    define_data (t_parser *parser);
void    handle_data(t_parser *parser);
#endif