# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luifer <luifer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/16 15:39:45 by kbolon            #+#    #+#              #
#    Updated: 2024/08/19 21:12:06 by luifer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D

SRCS = 	sources/main.c \
		sources/errors.c \
		sources/free_functions.c \
		sources/parsing/check_map.c \
		sources/parsing/read_input.c \
		sources/initialize_data.c \

#		arg_checker.c \

LIBFT = libft/libft.a
MLX_PATH = minilibx-linux
MLX = minilibx-linux/libmlx.a
CC = cc
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all: $(NAME) $(MLX)

$(NAME): $(OBJS)
	@make -C $(MLX_PATH)
	$(CC) $(CFLAGS) $(OBJS) -L$(MLX_PATH) -lmlx_Linux -lX11 -lXext -lm -o $(NAME) $(LIBFT)
	@echo "$(NAME): $(OBJS) was created"

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	rm -rf $(OBJS)
	@make clean -C $(MLX_PATH)
	@make clean -C libft
	@echo "$(NAME): $(OBJS) was deleted"

fclean: clean
		rm -rf $(NAME) $(MLX) $(LIBFT)
		@echo "$(NAME) $(MLX) $(LIBFT) was deleted"

re: fclean all

.PHONY: all clean fclean re