/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:09:34 by kbolon            #+#    #+#             */
/*                                                                            */
/*   Updated: 2024/08/19 14:45:58 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <memory.h>
# include <time.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>

# define PIXELS 64
# define WIDTH 640 
# define HEIGHT 480
# define XK_ESCAPE 0xff1b //Escape
# define FORWARD 0x77 //W
# define BACKWARD 0x73 //S
# define ROTATE_LEFT 0x61 //A
# define ROTATE_RIGHT 0x64 //D
# define LEFT 0xff51 //left arrow
# define RIGHT 0xff53 //right arrow

//Structure for the image it include:
//pointer to image, pointer to img address, bit per pixel
//line len, endian
typedef struct s_img
{
	void	*img; 
	int		*img_addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

//Structure for the text information of the game, it includes:
//pointer to path of north, south, east and west. Color of floor and ceiling
//
typedef struct s_textinfo
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				idx;
	double			step;
	double			position;
	int				x;
	int				y;
}	t_textinfo;

//Structure for map information, it includes:
//fd to open the map file, a counter of lines in the map, the map path
//file, height, width and index of the end of the map
typedef struct s_mapinfo
{
	int		fd;
	int		line_count;
	char	*path;
	char	**file;
	int		height;
	int		width;
	int		idx_map_end;
}	t_mapinfo;

//Structure for the ray it includes:
//camera, direction in x and y, map in x and y, steps in x and y
//side distance in x and y, delta distance in x and y, wall distance 
typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedistance_x;
	double	sidedistance_y;
	double	deltadistance_x;
	double	deltadistance_y;
	double	wall_distance;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

//Structure for the player, it includes:
//direction in which the player is oriented, position in x and y, direction in x and y
//plane in x and y, check if the player has moved, movement in x and y and rotation
typedef struct s_player
{
	char	direction;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		has_moved;
	int		move_x;
	int		move_y;
	int		rotate;
}	t_player;

//Structure to store the global data of the game, it includes:
//pointer to minilibx connection and window, window height and width, pointer to
//map, player, ray and textinfo. It also includes map and textures
typedef struct s_data
{
	void		*mlx_conn;
	void		*mlx_window;
	int			window_height;
	int			window_width;
	t_mapinfo	mapinfo;
	t_player	player;
	t_ray		ray;
	t_textinfo	textinfo;
	char		**map;
	int			**texture_pixels;
	int			**textures;
}	t_data;

//errors.c
void	error_message(char *str);
void	error_message_simple(char *str, char **arr);
int	error_input();

//initialize_data.c
void	ft_initialize_img(t_img *img);
void	ft_initialize_ray(t_ray *ray);
void	ft_initialize_map(t_mapinfo *mapinfo);
void	ft_initialize_player(t_player *player);
void	ft_initialize_data(t_data *data);


//free_functions.c
void	free_memory(char **arr);
//void	free_game(t_game *game);
//void	error_message_game(char *str, t_game *game);

//parsing/check_map.c
void	valid_chars(char **arr);
void	count_chars(char **arr, int *player);
void	check_map_items(char **arr);

//parsing/read_input.c
void	check_extension(char *s);
size_t	row_count(char **grid);
char	**read_map(char *s);
char	*ft_replace(char *s);
char	**graphic_gnl(int size, int fd, char **arr, int i);

#endif