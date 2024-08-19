# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/16 15:39:45 by kbolon            #+#    #+#              #
#    Updated: 2024/08/19 13:46:46 by kbolon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D

SRCS = 	sources/main.c \
		sources/errors.c \
		sources/free_functions.c \
		sources/parsing/check_map.c \
		sources/parsing/read_input.c \

#		arg_checker.c \

LIBFT = libft/libft.a
CC = cc -g
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

all: $(NAME) clean

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	rm -f $(OBJS)
	make clean -C libft

fclean: clean
		rm -f $(NAME)
		make fclean -C libft

re: fclean all

.PHONY: all clean fclean re