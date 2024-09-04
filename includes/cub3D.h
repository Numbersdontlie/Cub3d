/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:09:34 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/04 16:48:45 by kbolon           ###   ########.fr       */
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
# include <math.h>
# include <time.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>

# define PIXELS 64
# define WIDTH 640 
# define HEIGHT 480
# define MOVEMENTSPEED 0.0125
# define ROTATIONSPEED 0.015
# define XK_ESCAPE 0xff1b //Escape
# define FORWARD 0x77 //W
# define BACKWARD 0x73 //S
# define ROTATE_LEFT 0x61 //A
# define ROTATE_RIGHT 0x64 //D
# define LEFT 0xff51 //left arrow
# define RIGHT 0xff53 //right arrow
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define TRUE 10
# define FALSE 20


//set up enum for directions
typedef enum	e_direction
{
	N = 0,
	E = 1,
	S = 2,
	W = 3

} t_direction;

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
	char			*floor;
	char			**floor_rgb;
	char			*ceiling;
	char			**ceiling_rgb;
	char			**grid;
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
//file, height, width and index of tcharhe end of the map
typedef struct s_mapinfo
{
	int		fd;
	size_t	line_count;
	char	*path;//path to what?
	char	**grid;
	size_t	player_x; //we can move these, I just put to easy testing bc I only init map
	size_t	player_y; //we can move these, I just put to easy testing bc I only init map
	size_t	height;//could this be line count??
	size_t	width;
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
	t_img		img;
	char		**map;
	int			**texture_pixels;
	int			**textures;
}	t_data;

//errors.c
void		error_message(char *str);
void		error_message_simple(char *str, char **arr);
void		ft_malloc_error(void);
void		error_message_map(char *str, t_mapinfo *map);
void		error_message_text(char *str, t_textinfo *text);

//initialize_data.c
void		ft_initialize_img(t_img *img);
void		ft_initialize_ray(t_ray *ray);
//void		ft_initialize_map(t_mapinfo *mapinfo);
t_mapinfo 	*ft_initialize_map(char	*grid);
void		ft_initialize_player(t_player *player);
void		ft_initialize_data(t_data *data);

//initialize_window.c
int			ft_initialize_image(t_data *data, t_img *image, int width, int height);
int			ft_initialize_connection(t_data *data);
int			ft_initialize_texture_img(t_data *data, t_img *image, char *path);
int			*ft_put_img_into_buffer(t_data *data, char *path);
int			ft_initialize_textures(t_data *data);
int			filter_grid_lines(char *grid);


//free_functions.c
void		free_memory(char **arr);
void		ft_clean_exit(t_data *data);
void		free_text(t_textinfo *text);
void		free_and_make_null(void **ptr);
//void		free_game(t_game *game);
//void		error_message_game(char *str, t_game *game);

//parsing/check_map.c
void		valid_chars(t_textinfo *text);
void		count_chars(char **arr, size_t *player);
void		check_map_items(t_textinfo *text);

char		*ft_trim_line(char *str);

//parsing/flood_fill_check.c
int			find_item(char **grid, char axis);
int			path_checker(char **game, size_t y, size_t x);
void		flood_fill(char **game);

//parsing/helper_functions.c
void	copy_valid_lines(char *grid, char *trimmed, char **arr);
void	check_empty_lines(char **grid, int i);

//parsing/parse_input.c
char		*find_cardinal_paths(char **arr, char *s);
char		*find_floor_ceiling(char **arr, int c);
char		**remove_empty_lines(char **arr);
t_textinfo	*find_grid(t_textinfo *text, char **grid);
int			filter_grid_lines(char *grid);

//parsing/read_input.c
void		check_extension(char *s);
size_t		row_count(char **grid);
char		**read_map(char *s);
char		*ft_replace(char *s);
char		**graphic_gnl(int size, int fd, char **arr, int i);

//sources/moving/input_handler.c
int			ft_handle_key(int keysym, t_data *data);
int			ft_release_key(int keysym, t_data *data);
void		ft_initialize_events(t_data *data);

//sources/initializing/initialize_text.c
t_textinfo	*ft_initialize_textinfo(char **arr);
t_textinfo	*populate_floor_and_ceiling_values(t_textinfo *text, char **grid);
void		check_rgb_for_illegal_chars(t_textinfo *text, char **arr);

//sources/moving/initial_position.c
void		ft_initialize_nort_sout(t_player *player);
void		ft_initialize_weast_east(t_player *player);
void		ft_init_player_dir(t_data *data);

//sources/raycasting/implement_raycasting.c
void		ft_initialize_raycasting(int x, t_ray *ray, t_player *player);
void		ft_get_ray_step_and_distance(t_ray *ray, t_player *player);
void		ft_implement_dda(t_data *data, t_ray *ray);
void		ft_calculate_wall_height(t_data *data, t_player *player, t_ray *ray);
int			ft_make_raycasting(t_player *player, t_data *data);

//sources/helper_functions.c
void		print_map(char **arr);
char 		*path_extractor(char **arr, char *str);
char		*ft_strndup(const char *s, size_t n);
int			ft_strstr(char *str, char *to_find);

#endif