# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maddou <maddou@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 17:04:58 by mel-gand          #+#    #+#              #
#    Updated: 2023/07/07 15:23:49 by maddou           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = Minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./libf -g -fsanitize=address
# LDFLAGS = -lreadline -L/Users/mel-gand/.brew/opt/readline/lib -I/Users/mel-gand/.brew/opt/readline/include
RM = rm -rf
SRC = minishell.c libf/ft_putstr_fd.c libf/ft_isprint.c libf/ft_strcmp.c libf/ft_atoi.c libf/ft_isalpha.c libf/ft_itoa.c libf/ft_split.c libf/ft_strlen.c libf/ft_substr.c libf/ft_strdup.c  libf/ft_isalnum.c libf/ft_strjoin.c libf/ft_calloc.c  libf/ft_bzero.c lexer/tokenizer.c \
		lexer/split_pipe_heredoc.c lexer/check_unclosed_quotes.c lexer/tokenizer_error_one_arg.c lexer/split_token.c  lexer/split_spaces.c libf/ft_strnstr.c lexer/split_pipe_redir.c \
		lexer/count_tokens.c lexer/tokenizer_error_mult_arg.c parser/parser.c parser/fill_commands.c free_all_alloc.c parser/handle_data.c  parser/fill_ncmd_red.c parser/print_parser_argument.c\
		linked_list/add_node.c linked_list/creat_node.c linked_list/remove_node.c linked_list/length_node.c parser/wildcard.c\
		command/env/env_export.c command/env/export_command.c command/builtins.c command/cd.c command/echo.c command/pwd.c command/exit.c command/special_var.c \
		executor/executor.c executor/handle_cmd.c executor/handle_heredoc.c executor/find_path.c executor/redirections.c command/unset.c command/env/env_command.c executor/open_redir.c  \
		
		
OBJ := $(SRC:.c=.o)
OBJ := $(addprefix obj/, $(OBJ))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -lreadline $(OBJ) -o $(NAME) $(LDFLAGS)

obj/%.o: %.c
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re