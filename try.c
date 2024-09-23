
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
# define FALSE 
# define RED 0x7F7F7F

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
	char	*path;
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
	int				*floor_rgb;
	char			*ceiling;
	int				*ceiling_rgb;
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
//	char	*path;//path to what?
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
	int			image_height;
	int			image_width;
	t_mapinfo	*mapinfo;
	t_player	*player;
	t_ray		*ray;
	t_textinfo	*textinfo;
	t_img		*imginfo;
	int			*textures[6];//NESWFC
}	t_data;


//Function to initialize the textures information
//structure, it initialize all to NULL and 0
//except for the size, which is initialized to PIXELS (64)
t_textinfo	*ft_initialize_textinfo(char **arr)
{
	char		**grid;
	t_textinfo	*text;

	grid = read_map(*arr);
	if (!grid)
		error_message("ERROR: problem reading map");
	text = (t_textinfo *) ft_calloc (1, sizeof(t_textinfo));
	if (!text)
		error_message_simple("ERROR: calloc fail in text_init", grid);
	text->north = find_cardinal_paths(grid, "NO");
	text->south = find_cardinal_paths(grid, "SO");
	text->west = find_cardinal_paths(grid, "WE");
	text->east = find_cardinal_paths(grid, "EA");
	text->ceiling_rgb = populate_rgb_values(text, grid, 'C', \
		&text->hex_ceiling);
	text->floor_rgb = populate_rgb_values(text, grid, 'F', &text->hex_floor);
	text->size = PIXELS;
	text = find_grid(text, grid);
	if (!text->grid)
		error_message_text("ERROR: problems copying grid in init\n", text);
	free_memory(grid);
	return (text);
}

/*this function splits the rgb values for the floor and ceiling*/
int	*validate_and_convert(t_textinfo *text, char **arr, \
	unsigned long *hex_value)
{
	int		*rgb;
	int		i;

	i = -1;
	rgb = ft_calloc(3, sizeof(int));
	if (!rgb)
	{
		free_memory(arr);
		error_message_text("ERROR: problem with allocating rgb", text);
	}
	while (++i < 3)
	{
		rgb[i] = ft_atoi(arr[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			free(rgb);
			free_memory(arr);
			error_message_text("ERROR: rgb is not valid", text);
		}
	}
	*hex_value = ((rgb[0] & 0xff) << 16) + ((rgb[1] & 0xff) << 8) + \
		(rgb[2] & 0xff);
	return (rgb);
}

int	*populate_rgb_values(t_textinfo *text, char **grid, int c, 
	unsigned long *hex_value)
{
	char	*temp;
	char	**arr;
	int		*rgb;

	temp = find_floor_ceiling(text, grid, c);
	if (!temp)
	{
		free_memory(grid);
		error_message_text("ERROR: floor/ceiling values not found\n", text);
	}
	arr = ft_split(temp, ',');
	free(temp);
	if (!arr)
	{
		free_memory(grid);
		error_message_text("problem with splitting rgb", text);
	}
	if (check_rgb_for_illegal_chars(arr) == EXIT_FAILURE)
	{
		free_memory(grid);
		error_message_text("problem with splitting rgb", text);
	}
	rgb = validate_and_convert(text, arr, hex_value);
	free_memory(arr);
	return (rgb);
}


int	check_rgb_for_illegal_chars(char **arr)
{
	int		i;
	int		j;
	int		count;

	i = -1;
	count = row_count(arr);
	if (count < 3)
		error_message("ERROR: RGB not valid\n");
	while (++i < count)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			if (ft_isdigit(arr[i][j]))
				j++;
			else
				error_message("ERROR: RGB not valid\n");
		}
	}
	return (EXIT_SUCCESS);
}

//temp function to get the grid working for parse testing
void 	ft_initialize_map(t_data *data, t_textinfo *text)
{
	size_t		i;
	size_t		count;

	if (!data)
		return ;
	i = 0;
	data->mapinfo->line_count = row_count(text->grid);
	count = data->mapinfo->line_count;
	data->mapinfo->grid = (char **)ft_calloc (count + 1, sizeof(char *));
	if (!data->mapinfo->grid)
		error_message_data("ERROR: calloc fail in map_init", data, text);
	while (i < count)
	{
		data->mapinfo->grid[i] = ft_strdup(text->grid[i]);
		if (!data->mapinfo->grid[i])
			error_message_data("ERROR: ft_strdup fail in map_init", data, text);
		i++;
	}
	data->mapinfo->grid[i] = NULL;
	data->mapinfo->player_x = find_item(data->mapinfo->grid, 'x');
	data->mapinfo->player_y = find_item(data->mapinfo->grid, 'y');
}

//Function to initialize the global data of the program
t_data	*ft_initialize_data(t_textinfo *text)
{
	t_data		*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		error_message_text("ERROR: problems copying grid in init\n", text);
	data->textinfo = text;
	data->player = (t_player *)ft_calloc(1, sizeof(t_player));
	if (!data->player)
		error_message_data("ERROR: problems init player", data, text);
	data->ray = (t_ray *)ft_calloc(1, sizeof(t_ray));
	if (!data->ray)
		error_message_data("ERROR: problems init ray", data, text);
	data->mapinfo = (t_mapinfo *)ft_calloc(1, sizeof(t_mapinfo));
	if (!data->mapinfo)
		error_message_data("ERROR: problems init map", data, text);
	ft_initialize_map(data, text);
	return (data);
}
int	ft_initialize_imginfo(t_data *data)
{
	data->imginfo = (t_img *)ft_calloc(1, sizeof(t_img));
	if (!data->imginfo)
		error_message("ERROR: failed to initiate img\n");
	data->imginfo->img = mlx_new_image(data->mlx_conn, WIDTH, HEIGHT);
	if (!data->imginfo->img)
		error_message("ERROR: failed to create image\n");
	data->imginfo->img_addr = (int *)mlx_get_data_addr(data->imginfo->img, \
		&data->imginfo->bpp, &data->imginfo->line_len, &data->imginfo->endian);
	if (!data->imginfo->img_addr)
		error_message("ERROR: failed to get img address\n");
	return (EXIT_SUCCESS);
}


//Function to initialize the connection with the minilibx library
//it creates a connection with the library and creates a window
//into that connection. It also check that connection and window
//where created without problem
int	ft_initialize_connection(t_data *data)
{
	data->mlx_conn = mlx_init();
	if (!data->mlx_conn)
		error_message("ERROR: problems with mlx_init\n");
	data->mlx_window = mlx_new_window(data->mlx_conn, WIDTH, HEIGHT, "Cub3D");
	if (!data->mlx_window)
		error_message("ERROR: problems with mlx window\n");
	return (EXIT_SUCCESS);
}

//Function to initialize the textures into the image structure
//it will load the xmp file into an image and get the data address
/*int	ft_initialize_texture_image(t_data *data, t_img **image, char *path)
{
	if (!path)
		error_message("ERROR: path missing\n");
	check_path(path);
	(*image)->img = mlx_xpm_file_to_image(data->mlx_conn, path, \
		&data->image_width, &data->image_height);
	if (!(*image)->img)
		error_message("ERROR: failed to load texture image\n");
	(*image)->img_addr = (int *)mlx_get_data_addr\
		((*image)->img, &(*image)->bpp, &(*image)->line_len, &(*image)->endian);
	if (!(*image)->img_addr)
		error_message("ERROR: failed to get image address\n");
	return (EXIT_SUCCESS);
}*/

//Function to initialize the textures (NORTH, SOUTH, WEST, EAST)
//it allocate memory for the textures and call the put img into buffer function
//to load the textures in the data structure
int	ft_initialize_textures(t_data *data)
{
	data->textures[N] = mlx_xpm_file_to_image(data->mlx_conn, data->textinfo->north, &data->image_width, &data->image_height);
	data->textures[E] = mlx_xpm_file_to_image(data->mlx_conn, data->textinfo->east, &data->image_width, &data->image_height);
	data->textures[S] = mlx_xpm_file_to_image(data->mlx_conn, data->textinfo->south, &data->image_width, &data->image_height);
	data->textures[W] = mlx_xpm_file_to_image(data->mlx_conn, data->textinfo->west, &data->image_width, &data->image_height);
	if (!data->textures[N] || !data->textures[E] || !data->textures[S] || !data->textures[W])
		error_message("ERROR: problems loading textures\n");
	return (EXIT_SUCCESS);
}


void	error_message(char *str)
{
	ft_putstr_fd(str, 2);
	exit (EXIT_FAILURE);
}

void	error_message_simple(char *str, char **arr)
{
	if (arr)
		free_memory(arr);
	ft_putstr_fd(str, 2);
	exit (EXIT_FAILURE);
}

void	error_message_text(char *str, t_textinfo *text)
{
	free_text(text);
	ft_putstr_fd(str, 2);
	exit (EXIT_FAILURE);
}

void	error_message_data(char *str, t_data *data, t_textinfo *text)
{
	if (text)
		free_text(text);
	ft_putstr_fd(str, 2);
	ft_clean_exit(data);
/*	if (data->mlx_conn)
	{
		mlx_destroy_display(data->mlx_conn);
		free(data->mlx_conn);
	}
	free (data);*/
	exit (EXIT_FAILURE);
}

int	ft_wrapper_exit(t_data *data)
{
	ft_clean_exit(data);
	return (0);
}


void	free_memory(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

//Function to exit the program in a clean way
//it destroy the image, window and display before freeing memory
void	ft_clean_exit(t_data *data)
{
	free_textures(data);
	if (data->imginfo && data->imginfo->img)
	{
		mlx_destroy_image(data->mlx_conn, data->imginfo->img);
		free(data->imginfo);
	}
	if (data->mapinfo)
	{
		if (data->mapinfo->grid)
			free_memory(data->mapinfo->grid);
		free(data->mapinfo);
	}
	if (data->player)
		free(data->player);
	if (data->ray)
		free(data->ray);
	if (data->textinfo)
		free_text(data->textinfo);
	if (data->mlx_window)
		mlx_destroy_window(data->mlx_conn, data->mlx_window);
	if (data->mlx_conn)
	{
		mlx_destroy_display(data->mlx_conn);
		free(data->mlx_conn);
	}
	free(data);
}

void	free_text(t_textinfo *text)
{
	if (text)
	{
		if (text->north)
			free(text->north);
		if (text->south)
			free(text->south);
		if (text->east)
			free(text->east);
		if (text->west)
			free(text->west);
		if (text->grid)
			free_memory(text->grid);
		free(text);
	}
}

//at the moment, this frees N, E, S, W but does
//not include ceiling and floor
void	free_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->textures[i])
			mlx_destroy_image(data->mlx_conn, data->textures[i]);
		i++;
	}
}


int	main(int ac, char **av)
{
	t_textinfo	*text;
	t_data		*data;

	if (ac != 2)
		error_message("ERROR: include ./cub3D & .cub\n");
	check_extension(av[1]);
	text = ft_initialize_textinfo(&av[1]);
	if (!text)
		error_message("ERROR: problem loading text");
	check_args(text);
	data = ft_initialize_data(text);
	if (!data)
		error_message_text("ERROR: problem loading text", text);
	if (ft_initialize_connection(data) == EXIT_FAILURE)
		error_message_data("ERROR: problem initiating connection\n", data, text);
	if (ft_initialize_imginfo(data) == EXIT_FAILURE)
		error_message_data("ERROR: problem initiating imginfo\n", data, text);
	if (ft_initialize_textures(data) == EXIT_FAILURE)
		error_message_data("ERROR: problem initiating textures\n", data, text);
	ft_game(data);
	ft_initialize_events(data);
	ft_clean_exit(data);
	return (EXIT_SUCCESS);
}
