# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 17:04:58 by mel-gand          #+#    #+#              #
#    Updated: 2023/07/15 19:08:36 by mel-gand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = minishell
CC = cc
LDFLAGS = -lreadline -L/Users/mel-gand/.brew/opt/readline/lib
CFLAGS =   -Wall -Werror -Wextra -I./libf -I/Users/mel-gand/.brew/opt/readline/include #-fsanitize=address 
RM = rm -rf
SRC = minishell.c libf/ft_putstr_fd.c libf/ft_putchar_fd.c libf/ft_isprint.c libf/ft_strcmp.c libf/ft_atoi.c libf/ft_isalpha.c libf/ft_itoa.c libf/ft_split.c libf/ft_strlen.c libf/ft_substr.c libf/ft_strdup.c  libf/ft_isalnum.c libf/ft_strjoin.c libf/ft_calloc.c  libf/ft_bzero.c \
		ft_printf/ft_printchar.c ft_printf/ft_printf.c ft_printf/ft_printhex.c ft_printf/ft_printnbr.c ft_printf/ft_printpi.c ft_printf/ft_printstr.c ft_printf/ft_printuint.c lexer/tokenizer.c \
		lexer/split_pipe_heredoc.c lexer/check_unclosed_quotes.c lexer/tokenizer_error_one_arg.c lexer/split_token.c  lexer/split_spaces.c libf/ft_strnstr.c lexer/split_pipe_redir.c \
		lexer/count_tokens.c lexer/tokenizer_error_mult_arg.c parser/parser.c parser/fill_commands.c free_all_alloc.c parser/handle_data.c  parser/fill_ncmd_red.c parser/fill_redir.c \
		parser/fill_newcmd.c parser/check_dollar_expand.c parser/define_data_utils.c parser/expand_data.c parser/fill_define_data.c parser/find_dollar.c \
		linked_list/add_node.c linked_list/creat_node.c linked_list/remove_node.c linked_list/length_node.c parser/wildcard.c\
		commands/env/env_export.c commands/env/export_command.c commands/builtins.c commands/cd.c commands/echo.c commands/pwd.c commands/exit.c commands/special_var.c \
		executor/handle_cmd.c executor/handle_heredoc.c executor/find_path.c executor/redirections.c commands/unset.c \
		parser/check_exict_patern.c parser/find_mult_patern.c parser/find_number_newword_in_mul_arg.c parser/find_number_newword_in_one_arg.c parser/handal_wildcard_position.c parser/wildcard_utils.c \
		executor/special_var_heredoc.c commands/env/env_command.c commands/env/export_key.c commands/env/rm_rp_value.c \
		executor/open_redir.c executor/handle_multiple_cmd.c executor/handle_one_cmd.c  \
		executor/check_ambigious_utils.c  executor/check_ambigious.c executor/fill_newdata_beffor_after_check_ambigious.c \
		
		
OBJ := $(SRC:.c=.o)

all:  $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re