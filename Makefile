#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/15 18:23:50 by gmelisan          #+#    #+#              #
#    Updated: 2020/12/15 21:05:09 by gmelisan         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ping

LIBFT = ./libft

CC = @clang
CFLAGS = -Wall -Wextra #-Werror

OBJ = $(addprefix ./src/, \
main.o utils.o resolve.o\
)

all: $(NAME)

$(NAME): $(LIBFT)/libft.a $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -L$(LIBFT) -lft
	@printf "\033[0;32mFile $@ was successfully created.\033[0m\n"

$(OBJ): ./include/ft_ping.h

%.o: %.c
	$(CC) $(CFLAGS) -I./include -I$(LIBFT)/include -c -o $@ $<
	@printf "\033[1;34mCompiling ($(CFLAGS)) \033[0;36m$<\033[0m\n"

$(LIBFT)/libft.a:
	@make -C $(LIBFT)

clean:
	@rm -f $(OBJ)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)/libft.a

re: fclean all
