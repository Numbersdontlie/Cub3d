
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
	text->ceiling_rgb = populate_rgb_values(text, grid, 'C', &text->hex_ceiling);
	text->floor_rgb = populate_rgb_values(text, grid, 'F', &text->hex_floor);
	text->size = PIXELS;
	text = find_grid(text, grid);
	if (!text->grid)
		error_message_text("ERROR: problems copying grid in init\n", text);
	free_memory(grid);
	return (text);
}

/*this function splits the rgb values for the floor and ceiling*/
int	*validate_and_convert(t_textinfo *text, char **arr, unsigned long *hex_value)
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
	*hex_value = ((rgb[0] & 0xff) << 16) + ((rgb[1] & 0xff) << 8) + (rgb[2] & 0xff);
	return (rgb);
}

int	*populate_rgb_values(t_textinfo *text, char **grid, int c, unsigned long *hex_value)
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
	return(EXIT_SUCCESS);
}

//Function to initialize the image, it will initialize an empty image structure
//create the new image using the mlx library and check that was correctly created
//assign the image address
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
int	ft_initialize_textures(t_data *data)
{
	data->textures[N] = mlx_xpm_file_to_image(data->mlx_conn, data->textinfo->north, &data->image_width, &data->image_height);
	data->textures[E] = mlx_xpm_file_to_image(data->mlx_conn, data->textinfo->east, &data->image_width, &data->image_height);
	data->textures[S] = mlx_xpm_file_to_image(data->mlx_conn, data->textinfo->south, &data->image_width, &data->image_height);
	data->textures[W] = mlx_xpm_file_to_image(data->mlx_conn, data->textinfo->west, &data->image_width, &data->image_height);
	if (!data->textures[N] || !data->textures[E] || !data->textures[S] || !data->textures[W])
	{
		printf("Error loading texture: %s\n", data->textinfo->north);
		mlx_destroy_window(data->mlx_conn, data->mlx_window);
		mlx_destroy_display(data->mlx_conn);
		free(data->mlx_conn);
		return (1);	
	}
	return (EXIT_SUCCESS);
}

void	ft_get_texture_idx(t_data *data, t_ray *ray)
{
	if (ray->side == 1)
	{
		if (ray->dir_y > 0)
			data->textinfo->idx = S;
		else
			data->textinfo->idx = N;
	}
	else
	{
		if (ray->dir_x < 0)
			data->textinfo->idx = W;
		else
			data->textinfo->idx = E;
	}
}

//Function to update the texture pixels on the screen for render
//it calculates which part of the texture to apply to the current vertical line
//it flip the textures based on the direction the ray hits the wall
//it applies a shadow by applying a bitwise operation to darken textures based
//on the direction (north or east)
void	ft_update_texture(t_data *data, t_textinfo *texture, t_ray *ray, int x)
{
	int	y;
	int	color;

	ft_get_texture_idx(data, ray);
	texture->x = (int)(ray->wall_x * texture->size);
	if ((ray->side == 0 && ray->dir_x < 0) || \
		(ray->side == 1 && ray->dir_y > 0))
		texture->x = texture->size - texture->x - 1;
	texture->step = 1.0 * texture->size / ray->line_height;
	texture->position = (ray->draw_start - HEIGHT / 2 + \
		ray->line_height / 2) * texture->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		texture->x = (int)texture->position & (texture->size - 1);
		texture->position += texture->step;
		color = data->textures[texture->idx][texture->size \
			* texture->y + texture->x];
		if (texture->idx == N || texture->idx == E)
			color = (color >> 1) & RED;
		if (color > 0)
			data->textures[y][x] = color;
		y++;
	}
}
//function to render wall texture based on raycasting
void	ft_render_wall_texture(t_data *data, t_ray *ray, int x)
{
	int		y;
	int		colour;
	int		texture_x;
	int		texture_y;
	double	step;
	double	texture_pos;

	ft_get_texture_idx(data, ray);
	texture_x = (int)(ray->wall_x * (double)data->textinfo->size);
	if (ray->side == 0 && ray->dir_x > 0)
		texture_x = data->textinfo->size - texture_x - 1;
	step = 1.0 * data->textinfo->size/ray->line_height;
	texture_pos = (ray->draw_start - HEIGHT/2 + ray->line_height/2);
//renders texture line by line
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		texture_y = (int)texture_pos & (data->textinfo->size - 1);
		texture_pos += step;
		colour = data->textures[data->textinfo->idx][data->textinfo->size * texture_y + texture_x];
		if (ray->side == 1 && ray->dir_y  > 0)//south wall
			colour = (colour >> 1) & 8355711;
		ft_put_pixel_to_img(data->imginfo, x, y, colour);
		y++;
	}
}

//Function to initialize the raycast
//it will initialize the ray structure to zero and then assign
//values to camera, ray direction, ray position in map, and 
//distance to the nearest line in the x or y direction in grid (next neighbor)
void	ft_initialize_raycasting(int x, t_ray *ray, t_player *player)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->map_y = (int)player->pos_y;
	ray->map_x = (int)player->pos_x;
	ray->deltadistance_y = fabs(1 / ray->dir_y);
	ray->deltadistance_x = fabs(1 / ray->dir_x);
}

//Function to calculate the step and initial side distances
//the step_x and step_y determine the direction in which the ray
//moves through the grid. The sidedist_x and y represents
//the dist the ray must travel from current position to next grid
//line in x or y direction
void	ft_get_ray_step_and_distance(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedistance_x = (player->pos_x - ray->map_x) * ray->deltadistance_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedistance_x = (ray->map_x + 1.0 - player->pos_x) * ray->deltadistance_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedistance_y = (player->pos_y - ray->map_y) * ray->deltadistance_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedistance_y = (ray->map_y + 1.0 - player->pos_y) * ray->deltadistance_y;
	}
}

//Function to perform DDA, it will determine the distance
//to the next grid line in the x or y direction. The player
//will move through the grid and calculate the distance to the next
//grid line in x and y (it also notes which side of the wall was hit x or y)
void	ft_implement_dda(t_data *data, t_ray *ray)
{
	int	contact;

	contact = 0;
	while (contact == 0)
	{
		if (ray->sidedistance_x < ray->sidedistance_y)
		{
			ray->sidedistance_x += ray->deltadistance_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedistance_y += ray->sidedistance_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0.25 || ray->map_x < 0.25 || ray->map_y > data->mapinfo->height - 0.25 || ray->map_x > data->mapinfo->width - 1.25)
			break ;
		else if (data->mapinfo->grid[ray->map_y][ray->map_x] > '0')
			contact = 1;
	}
}

//Function to calculate the wall height based on the distance
//to the wall and the player's view angle. 1st we get the distance 
//to the wall and them derive the draw star and end position.
void	ft_calculate_wall_height(t_player *player, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_distance = (ray->sidedistance_x - ray->deltadistance_x);
	else
		ray->wall_distance = (ray->sidedistance_y - ray->deltadistance_y);
	ray->line_height = (int)(HEIGHT / ray->wall_distance);
	ray->draw_start = -(ray->line_height / 2) + (HEIGHT / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + (HEIGHT / 2);
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->wall_distance * ray->dir_y;
	else
		ray->wall_x = player->pos_x + ray->wall_distance * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

//Function to make the raycasting.  It iterates through the width of 
//screen and update the data to render the ray from the current position 
//and point of view of the player
//initializes ray, calculates steps and distances, performs DDA, 
//calculates wall height and updates textures
int	ft_make_raycasting(t_player *player, t_data *data)
{
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		ft_initialize_raycasting(x, data->ray, player);
		ft_get_ray_step_and_distance(data->ray, player);
		ft_implement_dda(data, data->ray);
		ft_calculate_wall_height(player, data->ray);
		ft_update_texture(data, data->textinfo, data->ray, x);
		x++;
	}
	return (EXIT_SUCCESS);
}


int	ft_game(t_data *data)
{
	mlx_clear_window(data->mlx_conn, data->mlx_window);
	ft_render_ceiling_and_floor(data);
	ft_make_raycasting(data->player, data);
	mlx_put_image_to_window(data->mlx_conn, data->mlx_window, \
		data->imginfo->img, 0 , 0);
	return (0);
}

void	ft_player_movement_forward_backword(t_data *data)
{
	if (data->player->move_y == 1)
	{
		if (data->mapinfo->grid[(int)(data->player->pos_y + data->player->dir_y \
			* MOVEMENTSPEED)][(int)(data->player->pos_x)] == '0')
			data->player->pos_y += data->player->dir_y * MOVEMENTSPEED;
		if (data->mapinfo->grid[(int)(data->player->pos_y)][(int)(data->player->pos_x \
			+ data->player->dir_x * MOVEMENTSPEED)] == '0')
			data->player->pos_x += data->player->dir_x * MOVEMENTSPEED;
	}
	if (data->player->move_y == -1)
	{
		if (data->mapinfo->grid[(int)(data->player->pos_y + data->player->dir_y \
			* MOVEMENTSPEED)][(int)(data->player->pos_x)] == '0')
			data->player->pos_y -= data->player->dir_y * MOVEMENTSPEED;
		if (data->mapinfo->grid[(int)(data->player->pos_y)][(int)(data->player->pos_x \
			+ data->player->dir_x * MOVEMENTSPEED)] == '0')
			data->player->pos_x -= data->player->dir_x * MOVEMENTSPEED;
	}
	data->player->move_y = 0;
}

void	ft_rotation(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;
	double	speed;

	if (data->player->rotate == 1)
		speed = -ROTATIONSPEED;
	else
		speed = ROTATIONSPEED;

	if (data->player->rotate == 1)
	{
		old_dir_x = data->player->dir_x;
		data->player->dir_x = data->player->dir_x * cos(speed) - \
			data->player->dir_y * sin(speed);
		data->player->dir_y = old_dir_x * sin(speed) + data->player->dir_y \
			* cos(speed);
		old_plane_x = data->player->plane_x;
		data->player->plane_x = data->player->plane_x * cos(speed) - \
			data->player->plane_y * sin(speed);
		data->player->plane_y = old_plane_x * sin(speed) + \
			data->player->plane_y * cos(speed);
	}
	data->player->rotate = 0;
}


void	ft_render_ceiling_and_floor(t_data *data)
{
	int	x;
	int	y;
	int	ceiling_colour;
	int	floor_colour;

	ceiling_colour = data->textinfo->hex_ceiling;
	floor_colour = data->textinfo->hex_floor;
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		{
			while (++x < WIDTH)
			{
				if (y < HEIGHT/2)
					ft_put_pixel_to_img(data->imginfo, x, y, ceiling_colour);
				else
					ft_put_pixel_to_img(data->imginfo, x, y, floor_colour);
			}
		}
	}
}

void	ft_put_pixel_to_img(t_img *imginfo, int x, int y, int colour)
{
	char	*pixel;
	int		bytes_per_pixel;

	bytes_per_pixel = imginfo->bpp/8;
	pixel = (char *)imginfo->img_addr + (y * imginfo->line_len + x * bytes_per_pixel);
	*(unsigned int *)pixel = colour;
}

void	ft_initialize_north_south(t_player *player)
{
	if (player->direction == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (player->direction == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else
		return ;
}

void	ft_initialize_west_east(t_player *player)
{
	if (player->direction == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (player->direction == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0;
	}
	else
		return ;
}

void	ft_init_player_dir(t_data *data)
{
	ft_initialize_north_south(data->player);
	ft_initialize_west_east(data->player);
}

int	ft_handle_key(int keysym, t_data *data)
{
	if (keysym == XK_ESCAPE)
		on_destroy(data);
	if (keysym == LEFT)
		data->player->rotate -= 1;
	if (keysym == RIGHT)
		data->player->rotate += 1;
	if (keysym == FORWARD)
		data->player->move_y = 1;
	if (keysym == BACKWARD)
		data->player->move_y = -1;
	if (keysym == ROTATE_LEFT)
		data->player->move_x = -1;
	if (keysym == ROTATE_RIGHT)
		data->player->move_x = 1;
	return (0);
}

int on_destroy(t_data *data)
{
	if (data->mlx_window)
		mlx_destroy_window(data->mlx_conn, data->mlx_window);
	mlx_loop_end(data->mlx_conn);
	if (data->mlx_conn)
	{
		mlx_destroy_display(data->mlx_conn);
		free(data->mlx_conn);
	}
	exit(0);
	return (0);
}


void	ft_initialize_events(t_data *data)
{
	mlx_hook(data->mlx_window, KeyRelease, KeyReleaseMask, &ft_handle_key, data);
	mlx_loop(data->mlx_conn);
	if (data->mlx_conn)
	{
		mlx_destroy_display(data->mlx_conn);
		free(data->mlx_conn);
	}
}


void check_args(t_textinfo *text)
{
	valid_chars(text);
	check_map_items(text);
	flood_fill(text->grid);
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
		error_message_data("ERROR: problem initiating imginfo\n", data, NULL);
	ft_game(data);
	ft_initialize_events(data);
	if (data->mlx_conn)
	{
		mlx_destroy_display(data->mlx_conn);
		free(data->mlx_conn);
	}
	ft_clean_exit(data);
	free_text(text);
	free(text);
	free(data);
	return (EXIT_SUCCESS);
}
