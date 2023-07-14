/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:12:52 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/14 11:59:10 by maddou           ###   ########.fr       */
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
#include"ft_printf/ft_printf.h"
#include <errno.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
# include <dirent.h>
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

extern int g_exit;

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
    WALLO,
}   t_dt;

typedef struct s_lexer
{
	t_env *env;
	t_env *exp;
	char **ar_env;
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
	char *copy_data;
	int  ex_dollar;
}   t_data;

typedef  struct s_red{
    int name;
    char *data;
	char *copy_data;
    int  ex_dollar;
	int  check_amb;
	int *fd;
} t_red;

typedef struct s_commands
{
	char **cmd;
	int nb_cmd; // hada 3la hsab trus false min nal9a command ndiro 1 bash mayw93lich mochkil f define data 
	int dt_nb;
	t_data *dt;
	int ext_dollar;
	int i;
	int nb_red;
    char **new_cmd;
    t_red *red;
}   t_cmd;

typedef struct s_parser
{
	t_cmd *comm;
	t_lexer *lex;
	int nb_arg;
}   t_parser;

//------------------start linked--------------//
void add_node(t_env *node,t_env **head);
t_env *creat_list(int nb);
t_env *creat_node(char *data);
//t_env *remove_node(t_env *head, char *id);
void remove_node(t_env **head, char *id);
int length(t_env *env);
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
int split_pipe_heredoc(t_lexer *lex);
void count_tokens (t_lexer *lex);
// int find_end_utils(t_lexer *lex);
int split_quotes(char *line, int i);
void define_word_token(t_lexer *lex);

//--------------error-------------//
int quotes_error(t_lexer *lex);
int pipe_error(t_lexer *lex);
int redir_pipe_error_one_arg(t_lexer *lex);
int redir_pipe_error_mult_arg(t_lexer *lex);
// int tokenizer_error(t_lexer *lex);



//-----------parsing-----------//
int		parser(t_lexer *lex);
void	fill_command (t_parser *parser);
int		count_red(t_cmd *comm);
void	fill_red(t_cmd *comm, int nb);
int		check_red(t_cmd *comm, int i);
int		count_newcmd(char *data);
void	check_and_fill_newcmd(t_cmd *comm);
void	ft_split_data(t_cmd *comm, int i, int *j);
void	handle_data(t_parser *parser);

//-------command/builtins------//
void	builtin_commands(t_parser *parser, int i);
char    *get_env(t_parser *parser, char *str);
void    update_env(t_parser *parser,char *var);
void	echo_command(char **argv);
void	cd_command(t_parser *parser, char **argv);
void	pwd_command(void);
void	exit_command(t_parser *parser, char **argv);
char    *special_var(char **argv);
int		alloc_newarg(char *argv);
char	*copy(char *newarg, char *g_exit, int *idx);
void	export_command(t_parser * parser, int i);
void	ft_tran_env(t_lexer *lex);
void    fill_dt_utils(char *env, t_env *tmp1, t_env *tmp2, char ev);
void	env_command(t_parser *parser, int i);
int		check_valid_key(char *str);
int		find_ed (char *env, int i, int check);
void	unset_command(t_parser *parser);
//-----------executor----------//
void    	executor(t_parser *parser);
void		handle_cmd(t_parser *parser);
int			is_builtin(char **cmd);
void		exec_cmd_in_pipe(t_parser *parser,int *cid, int i, int fd_her);
void		exec_one_cmd(t_parser *parser, int *cid, int i, int fd_her);
void		print_error(t_parser *parser, char *execpath, int i);
void		fd_error(t_parser *parser);
void		dup_and_close(t_parser *parser, int fd_in, int fd_out, int i);
void		waitchild_and_save_exit(int *cid, int i);
int			handle_heredoc(t_parser *parser, int i);
char		*special_var_in_heredoc(char *input);
int			check_special_variable(char *input);
char* const	*find_execpath(t_parser *parser, int i);
void		exec_cmd(t_parser *parser, int i);
int			check_redirect(t_cmd *cmd, int fd_her);
int			check_ambiguous( t_red*red);
int			open_redirect(t_cmd *cmd, int fd_her);


int		parser(t_lexer *lex);
void	fill_command (t_parser *parser);
void	fill_newcmd_red(t_parser *parser);
void	define_data(t_cmd *comm, char *data, int pos);
int		find_data_redir(int *name, char *data);
void	check_pos_one(t_cmd *comm, char *data, int pos);
void	handle_data(t_parser *parser);
char	*copy_quote(char *data, int *i, char *new_data);
void	fill_data(t_cmd comm);
int		check_ex_dollar(char *data);
int		check_if_dollar_expand(char *data, char c, int j);
int		check_valid(char *data, int i);
int		ft_check_expand_delimiter(char *delimiter);
void	find_dollar(t_parser *parser, t_cmd *cmd);
char	*find_dollar_utils(t_parser *parser, char *data, int j, char e);
void	check_dollar(t_parser *parser, char *dquote, char **new_data);
void	expand_data (t_env *env, char *data, int *j, char **new_data);
int		check_exit(t_env *env, char *envmnt, char **new_data);
int		check_valid(char *data, int i);
char	*ft_copier(char add, char *new_data);
int		check_quote(char *data, int i);
void	handal_wildcard(t_parser *parser, t_cmd *cmd);


void free_parser(t_parser *parser);

void print(t_parser *parser, int nb_red, int nb_newcmd, int i);
//-----------squipe quote----------//
char *if_quote_fill(char *data, int *u, char *new_cmd);

//-----------squipe quote----------//

//-----------------wildcard-------------------//

//--------------utils-----------//
void ft_calcule_etoile(char *data, int *i);
int check_position_etoile(char *data, char c);
int check_valid_first(char *entry_name, char *patern);
int check_valid_last(char *entry_name, char *patern);
int lenght_patern(char **patern);
//--------------utils-----------//
int *check_exict_patern(t_parser *parser, char *data, int *nb_w, DIR *OPENFILE) ;
int count_nb_newdt(int *nb_w, int i);
//--------find_nw_one_arg-------//
int *find_number_w_one_arg(char *data, int *nb_w, char **patern);
int *find_patern_one_etoile(int *nb_w, char c, char **patern);
void initialization_new_dt(int j, int k, t_data *new_dt, t_cmd *cmd);
t_data *cop_current_dt(t_cmd *cmd, int j, int *nb_w, int i);
//--------find_nw_one_arg-------//
int *find_number_w_mult_arg(t_parser *parser, int *nb_w, char **patern, int nb_arg);
//--------wildcard_position-------//
int *findnbw_in_fl(char *entry_center, char **patern, int *nb_w, int j);
int *findnbw_in_f(char *entry_center, char **patern, int *nb_w, int j);
int *findnbw_in_l(char *entry_center, char **patern, int *nb_w, int j);
int *findnbw_in(char *entry_center, char **patern, int *nb_w, int j);
//--------wildcard_position-------//
char *find_entry_center(char *entry_name, char *patern, char k);
int find_begining_patern(char *entry_name, char *patern, int *i, int *j);
int *find_mult_etoile(int *nb_w, char *data, char **patern, DIR *OPENFILE);
int *ft_tout_file(int *nb_w, DIR *OPENFILE, t_parser *parser);

void initialization_data_cmd(char *entry_d_name, t_cmd *cmd, int j);
t_data *fill_wildcard_data(t_cmd *cmd, int j, int *nb_w);
//-----------------wildcard-------------------//
void rl_replace_line (const char *, int);
#endif