/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:12:52 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/08 01:04:19 by mel-gand         ###   ########.fr       */
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
#include <errno.h>
#include <limits.h>

/*
t_list {
	void *content;
	t_list *next;
}
t_env {
	char *key;
	char *value;
}

void    destroy_env(t_env *var)
{
	free(var->key);
	free(var->value);
	free(var);
}

typedef void    (*t_lstdel)(void *);

env_node = malloc(sizeof(t_list));
env_entry = malloc(sizeof(t_env));
env_node->content = env_entry;

ft_lstclear(&lst, (t_lstdel) destroy_env);
*/

typedef struct s_env {
	char *all;
	char *key;
	char *value;
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
	t_env *env;
	t_env *exp;
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
	int  ex_dollar;
}   t_data;

typedef struct s_commands
{
	char **cmd;
	int nb_cmd;
	int dt_nb;
	t_data *dt;
	int ext_dollar;
	int i;
}   t_cmd;

typedef struct s_parser
{
	t_cmd *comm;
	t_lexer *lex;
}   t_parser;

//------------------start linked--------------//
t_env *add_node(t_env *head);
t_env *creat_list(int nb);
t_env *creat_node(t_env *head);
t_env *remove_node(t_env *head, char *id);
//-------------------end linked-------------//

//------------------start command--------------//
void creating_new_env(t_lexer *lex, char **env);
//------------------end command--------------//


//---------free-------//
void free_double_array(char **str);


//------------lexer---------------//

int tokenizer(t_lexer *lex);
int check_unclosed_quotes(char *str);
int skip_quote(char *line, int i);
int dquote(char *str, int *i);
int quote(char *str, int *i);


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
int		parser(t_lexer *lex);
void	fill_command (t_parser *parser);
// void    define_data (t_parser *parser);
void	handle_data(t_parser *parser);

//-------command/builtins------//
void	builtin_commands(char **argv);
void	echo_command(char **argv);
void	cd_command(char **argv);
void	pwd_command(char **argv);
void	exit_command(char **argv);

#endif