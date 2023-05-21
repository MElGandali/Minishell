# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 17:04:58 by mel-gand          #+#    #+#              #
#    Updated: 2023/05/21 17:37:19 by mel-gand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./libf
LDFLAGS = -lreadline -L/Users/mel-gand/.brew/opt/readline/lib -I/Users/mel-gand/.brew/opt/readline/include
RM = rm -rf
SRC = minishell.c libf/ft_strcmp.c libf/ft_split.c libf/ft_strlen.c libf/ft_substr.c libf/ft_strdup.c libf/ft_strjoin.c lexer/tokenizer.c \
		lexer/check_unclosed_quotes.c lexer/tokenizer_error_one_arg.c lexer/split_token.c  lexer/split_spaces.c lexer/define_word_token.c libf/ft_strnstr.c lexer/split_pipe_redir.c \
		lexer/count_tokens.c lexer/tokenizer_error_mult_arg.c parser/parser.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c philo.h
	@$(CC) -c $(CFLAGS) $< -o $@ minishell.h libft/libft.h

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re