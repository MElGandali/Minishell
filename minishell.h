/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:12:52 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/10 13:22:55 by maddou           ###   ########.fr       */
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

typedef struct s_lexer
{
    int i;
    int start;
    char **lexer;
    char **word;
    int word_nb;
    char *line;
    int token_nb;
}           t_lexer;

void tokenizer(t_lexer *lex);
void handle_quotes(char *str);

void tokenizer_error(char *str);

// split token
void split_token(t_lexer *lex);
char **split_spaces(t_lexer *lex);
#endif