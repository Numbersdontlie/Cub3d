# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/16 15:39:45 by kbolon            #+#    #+#              #
#    Updated: 2024/09/19 19:14:12 by kbolon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = 	sources/main.c \
		sources/errors.c \
		sources/free_functions.c \
		sources/parsing/check_map.c \
		sources/parsing/flood_fill_check.c \
		sources/parsing/helper_functions.c \
		sources/parsing/parse_input.c \
		sources/parsing/read_input.c \
		sources/initializing/initialize_data.c \
		sources/initializing/initialize_text.c \
		sources/moving/input_handler.c \
		sources/initializing/initialize_window.c \
		sources/moving/initial_position.c \
		sources/raycasting/rendering.c \
		sources/raycasting/implement_raycasting.c \
		sources/raycasting/handle_textures.c
#		sandbox/load_image.c

LIBFT = libft/libft.a
MLX_PATH = minilibx-linux
MLX = $(MLX_PATH)/libmlx.a
CC = cc
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g -I/opt/X11/include -fsanitize=address

#colours

RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
MAGENTA=\033[0;35m
CYAN=\033[0;36m
RESET=\033[0m

all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
#	$(CC) $(CFLAGS) $(OBJS) -L$(MLX_PATH) -lmlx_Linux -lX11 -lXext -lm -o $(NAME) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(MLX_PATH) -lmlx -L/opt/X11/lib -lX11 -lXext -lm -o $(NAME) $(LIBFT)
	@$(MAKE) clean
	@$(MAKE) clear-screen
	@echo "$(BLUE)cub3D compiled$(RESET)"

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
	@$(MAKE) clear-screen
	@echo "$(RED)object files were deleted$(RESET)"

clear-screen:
	clear
	@echo "$(YELLOW)Terminal cleared after build process$(RESET)"

fclean: clean
		rm -rf $(NAME) $(MLX) $(LIBFT)
		@$(MAKE) clear-screen
		@echo "$(MAGENTA)$(NAME) $(MLX) $(LIBFT) was deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re