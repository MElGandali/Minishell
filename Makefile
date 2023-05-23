# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maddou <maddou@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 17:04:58 by mel-gand          #+#    #+#              #
#    Updated: 2023/05/22 21:46:37 by maddou           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./libf -g -fsanitize=address
LDFLAGS = -lreadline -L/Users/mel-gand/.brew/opt/readline/lib -I/Users/mel-gand/.brew/opt/readline/include
RM = rm -rf
SRC = minishell.c libf/ft_strcmp.c libf/ft_split.c libf/ft_strlen.c libf/ft_substr.c libf/ft_strdup.c libf/ft_strjoin.c lexer/tokenizer.c \
		lexer/check_unclosed_quotes.c lexer/tokenizer_error_one_arg.c lexer/split_token.c  lexer/split_spaces.c lexer/define_word_token.c libf/ft_strnstr.c lexer/split_pipe_redir.c \
		lexer/count_tokens.c lexer/tokenizer_error_mult_arg.c parser/parser.c parser/fill_commands.c
OBJ := $(SRC:.c=.o)
OBJ := $(addprefix obj/, $(OBJ))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

obj/%.o: %.c
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re