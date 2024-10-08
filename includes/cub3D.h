/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:09:34 by kbolon            #+#    #+#             */
/*   Updated: 2024/10/08 21:52:47 by kbolon           ###   ########.fr       */
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
# define MOVE_LEFT 0x61 //A
# define MOVE_RIGHT 0x64 //D
# define ROTATE_LEFT 0xff51 //left arrow
# define ROTATE_RIGHT 0xff53 //right arrow
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define TRUE 10
# define FALSE 20
# define RED 0x7F7F7F
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define MAGENTA_BURST 0xFF00FF
# define LIME_SHOCK 0xCCFF00
# define NEON_ORANGE 0xFF6600
# define PSYCHEDELIC_PURPLE 0x660866
# define ELECTRIC_BLUE 0x0066FF
# define LAVA_RED 0xFF3300

# ifndef BONUS
#  define BONUS 1
# endif

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
	int		texture_width;//width of the texture
	int		texture_height;//height of the texture
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;


//Structure for the text information of the game, it includes:
//pointer to path of north, south, east and west. Color of floor and ceiling
//
typedef struct s_textinfo
{
	char			**paths;
	int				*floor_rgb;
	int				*ceiling_rgb;
	char			**grid;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
//	int				size;//what is this for?
	int				idx;
	double			step;
	double			pos;
	int				x;
	int				y;
}	t_textinfo;

//Structure for map information, it includes:
//fd to open the map file, a counter of lines in the map, the map path
//file, height, width and index of tcharhe end of the map
typedef struct s_mapinfo
{
	int		fd;
	char	**grid;
	size_t	player_x; //we can move these, I just put to easy testing bc I only init map
	size_t	player_y; //we can move these, I just put to easy testing bc I only init map
	size_t	map_height;//line count??
	size_t	map_width;
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

typedef struct s_mini
{
	char	**map;
	t_img	*img;
	int		size;
	int		dist;
	int		tile;
	int		mini_y;//offset
	int		mini_x;//offset
}	t_mini;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;


//Structure to store the global data of the game, it includes:
//pointer to minilibx connection and window, window height and width, pointer to
//map, player, ray and textinfo. It also includes map and textures
typedef struct s_data
{
	void			*mlx_conn;
	void			*mlx_window;
	char			**map;//will charge the map in an array to access from function to check movement
	char			**path;
	t_mapinfo		*mapinfo;
	t_player		*player;
	t_ray			*ray;
	t_textinfo		*textinfo;
	t_img			*textureinfo[4];
//	t_img			*imginfo;//do we need?
//	t_img			background;//do we need?
	int				**texture_pixels;//other mcombo
//	int				**textures;//other mcombo
	t_mini			minimap;//only for bonus if we do it
}	t_data;

//sources/initialize/initialize_data.c
int 		ft_initialize_map(t_data *data, t_textinfo *text);
int			ft_initialize_data(t_data **data, t_textinfo *text);
int			ft_init_background(t_data *data);

//sources/initializing/initialize_text.c
t_textinfo	*ft_initialize_textinfo(char **arr);
int			fill_paths(t_textinfo *text, char **grid);
int			*validate_and_convert(t_textinfo *text, char **grid, unsigned long *hex_value);
int			*populate_rgb_values(t_textinfo *text, char **grid, int c, unsigned long *hex_value);
int			check_rgb_for_illegal_chars(char **arr);

//sources/initialize/initialize_window.c
int			ft_initialize_connection(t_data *data);
int			ft_initialize_textures(t_data *data);
int			ft_clear_textures(t_data *data);
int			ft_init_texture_img(t_data *data, t_img *image, char *path);
int	ft_init_img(t_data *data, t_img *image);

//sources/initialize/render_image.c
int			ft_launch_game(t_data *data);
int			ft_render(t_data *data);
void		ft_put_pixel_to_img(t_img *imginfo, int x, int y, int colour);
void 		render_scaled_texture_on_base(t_data *data, int texture_idx, void *sky_floor_img);
void		render_sky_floor_base(unsigned int sky, unsigned int floor, t_data *data);
int			ft_initialize_imginfo(t_data *data);
void		ft_init_game(t_data *data);
void		ft_draw_image_in_window(t_data *data);
void	ft_init_texture_pixels(t_data *data);

//sources/moving/check_position.c
int			ft_check_if_empty(t_data *data, double x, double y);
int			ft_check_if_inside_map(double x, double y);
int			ft_allow_movement(t_data *data, double x, double y);
int			ft_validate_movement(t_data * data, double x_after, double y_after);

//sources/moving/initial_position.c
void		ft_initialize_north_south(t_player *player);
void		ft_initialize_west_east(t_player *player);
void		ft_init_player_dir(t_data *data);

//sources/moving/input_handler.c
int			ft_handle_key(int keysym, t_data *data);
int			ft_release_key(int keysym, t_data *data);
void		ft_loop_events(t_data *data);
int			on_destroy(t_data *data);

//sources/moving/move_player.c
void		ft_player_movement_forward_backword(t_data *data);
void		ft_rotation(t_data *data);
int			ft_move_player_fw(t_data *data);
int			ft_move_player_bw(t_data *data);
int			ft_move_player_left(t_data *data);
int			ft_move_player_right(t_data *data);
int			ft_move_player(t_data *data);

//sources/moving/rotate.c
int			ft_rotate_player_dir_vector(t_data *data, double speedrot);
int			ft_execute_rotation(t_data *data, double dirrot);

//parsing/check_map.c
void		valid_chars(t_textinfo *text);
void		count_chars(char **arr, size_t *player);
void		check_map_items(t_textinfo *text);
char		*ft_trim_line(char *str);
int			filter_grid_lines(char *grid);

//parsing/flood_fill_check.c
int			find_item(char **grid, char axis);
int			path_checker(char **game, size_t y, size_t x);
void		flood_fill(char **game);

//sources/helper_functions.c
void		copy_valid_lines(char *grid, char *trimmed, char **arr);
void		check_empty_lines(char **grid, int i);
char		*ft_strndup(const char *s, size_t n);
void		print_map(char **arr);
int			ft_strstr(char *str, char *to_find);

//parsing/parse_input.c
char		*find_cardinal_paths(char **arr, char *s);
char 		*path_extractor(char **arr, char *str);
char		*find_floor_ceiling(t_textinfo *text, char **arr, int c);
char		**remove_empty_lines(char **arr);
t_textinfo	*find_grid(t_textinfo *text, char **grid);

//parsing/read_input.c
void		check_extension(char *s);
size_t		row_count(char **grid);
char		**read_map(char *s);
char		*ft_replace(char *s);
char		**graphic_gnl(int size, int fd, char **arr, int i);

//sources/raycasting/handle_textures.c
void		ft_update_texture(t_data *data, int *text, t_ray *ray, int x);
void		ft_render_wall_texture(t_data *data, t_ray *ray, int x);
void		ft_get_texture_idx(t_data *data, t_ray *ray);

//sources/raycasting/implement_raycasting.c
void		ft_initialize_raycasting(int x, t_ray *ray, t_player *player);
void		ft_get_ray_step_and_distance(t_ray *ray, t_player *player);
void		ft_implement_dda(t_data *data, t_ray *ray);
void		ft_calculate_wall_height(t_ray *ray);//, t_player *player);
int			ft_make_raycasting(t_player *player, t_data *data);
void		ft_calculate_texture_coordinates(t_data *data, t_ray *ray);
void	 	ft_render_texture(t_data *data, t_ray *ray, int x);

//sources/errors.c
void		error_message(char *str);
int			error_message_simple(char *str, char **arr);
void		error_exit(char *str, t_data *data, t_textinfo *text);
void		error_message_text(char *str, t_textinfo *text);

//sources/free_functions.c
void		free_memory(char **arr);
void		ft_exit_game(t_data *data);
void		ft_clean_exit(t_data *data);
void		free_text(t_textinfo *text);
void		free_textures(t_data *data);

//sources/free_functions2.c
void		free_mapstruct(t_data *data);
void	free_tab(void **tab);
void free_partial(int **array, int rows);

//sources/bonus/mini_map.c
int		ft_launch_game_bonus(t_data *data);
void	make_tiles(t_data *data, int x, int y, int colour);
void	render_map_bonus(t_data *data);
void 	render_sky_floor_base_bonus(unsigned int sky, unsigned int floor, t_data *data);
void 	render_scaled_texture_on_base_bonus(t_data *data, int texture_idx, void *sky_floor_img);
void	render_player_bonus(t_data *data);

#endif