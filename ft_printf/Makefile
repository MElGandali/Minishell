# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 22:09:04 by mel-gand          #+#    #+#              #
#    Updated: 2023/07/09 15:32:32 by mel-gand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftft_printf.a
CC = gcc
AR = ar rc

CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
SRC = ft_printf.c ft_printstr.c ft_printnbr.c ft_printchar.c ft_printuint.c ft_printhex.c ft_printpi.c
OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME):$(OBJ)
	@$(AR) $@ $^

%.o:%.c ft_printf.h
	@$(CC) -c $< -o $@

clean:
	@$(RM) $(OBJ)
fclean: clean
	@$(RM) $(NAME)
re: fclean all

.PHONY: all clean re
