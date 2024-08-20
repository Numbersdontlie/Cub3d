# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/16 15:39:45 by kbolon            #+#    #+#              #
#    Updated: 2024/08/20 14:35:14 by kbolon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D

SRCS = 	sources/main.c \
		sources/errors.c \
		sources/free_functions.c \
		sources/parsing/check_map.c \
		sources/parsing/flood_fill_check.c \
		sources/parsing/read_input.c \
		sources/initialize_data.c \

#		arg_checker.c \

LIBFT = libft/libft.a
MLX_PATH = minilibx-linux
MLX = minilibx-linux/libmlx.a
CC = cc
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(MLX_PATH) -lmlx_Linux -lX11 -lXext -lm -o $(NAME) $(LIBFT)
#	@echo "$(NAME): $(OBJS) was created"
	@$(MAKE) clean
	@$(MAKE) clear-screen

$(MLX):
	@make -C $(MLX_PATH)

$(LIBFT):
	@make -C libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	rm -rf $(OBJS)
	@make clean -C $(MLX_PATH)
	@make clean -C libft
#	@echo "$(NAME): $(OBJS) was deleted"

clear-screen:
	clear
	@echo "Terminal cleared after build process"

fclean: clean
		rm -rf $(NAME) $(MLX) $(LIBFT)
#		@echo "$(NAME) $(MLX) $(LIBFT) was deleted"

re: fclean all

.PHONY: all clean fclean re