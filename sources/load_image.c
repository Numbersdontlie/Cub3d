#include "../includes/cub3D.h"

void	error_exit(char *str, t_data *data, t_textinfo *text)
{
	if (text)
		free_text(text);
	if (data)
		ft_clean_exit(data);
	ft_putstr_fd(str, 2);
	exit (EXIT_FAILURE);
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

void	ft_exit_game(t_data *data)
{
	free_textures(data);
	if (data->mlx_window)
		mlx_destroy_window(data->mlx_conn, data->mlx_window);
	if (data->mlx_conn)
	{
		mlx_loop_end(data->mlx_conn);
		mlx_destroy_display(data->mlx_conn);
		free(data->mlx_conn);
	}
	ft_clean_exit(data);
}

//Function to exit the program in a clean way
//it destroy the image, window and display before freeing memory
void	ft_clean_exit(t_data *data)
{
	if (data->path)
		free_memory(data->path);
	if (data->mapinfo)
		free_mapstruct(data);
	if (data->player)
		free(data->player);
	if (data->ray)
		free(data->ray);
	if (data->textinfo)
		free_text(data->textinfo);
	free(data);
	exit(EXIT_SUCCESS);
}

void	free_text(t_textinfo *text)
{
	if (text)
	{
		if (text->paths)
			free_memory(text->paths);
		if (text->ceiling_rgb)
			free(text->ceiling_rgb);
		if (text->floor_rgb)
			free(text->floor_rgb);
		if (text->grid)
			free_memory(text->grid);
		free(text);
	}
}

void	free_textures(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (data->textureinfo[i]->img)
			mlx_destroy_image(data->mlx_conn, data->textureinfo[i]->img);
		if (data->textureinfo[i])
			free(data->textureinfo[i]);
	}
}

void	free_mapstruct(t_data *data)
{
	if (data->mapinfo->grid)
	{
		free_memory(data->mapinfo->grid);
		data->mapinfo->grid = NULL;
	}
	if (data->mapinfo)
	{
		free(data->mapinfo);
		data->mapinfo = NULL;
	}
}

int on_destroy(t_data *data)
{
	ft_exit_game(data);
	free(data);
	exit(0);
	return (0);
}

int on_keypress(int keysym, t_data *data)
{
	printf("Pressed key: %d\n", keysym);
	if (keysym == 65307) // Escape key to close the window
	{
		on_destroy(data);  // Close window on ESC key press
	}
	return (0);
}

// Function to render the sky/floor background once and store it in `sky_floor_img`
void render_sky_floor_base(unsigned int sky, unsigned int floor, void *sky_floor_img)
{
	int x, y;
	int *img_addr;
	int bpp, line_len, endian;

	// Get the image address for the background image
	img_addr = (int *)mlx_get_data_addr(sky_floor_img, &bpp, &line_len, &endian);

	for (y = 0; y < HEIGHT / 2; y++)  // Top half for sky
	{
		for (x = 0; x < WIDTH; x++)
		{
			img_addr[y * (line_len / 4) + x] = sky; // Sky color
		}
	}
	for (y = HEIGHT / 2; y < HEIGHT; y++)  // Bottom half for floor
	{
		for (x = 0; x < WIDTH; x++)
		{
			img_addr[y * (line_len / 4) + x] = floor; // Floor color
		}
	}
}

// Function to render a texture (1/4 size) on top of the sky/floor base image
void render_scaled_texture_on_base(t_data *data, int texture_idx, void *sky_floor_img)
{
	int x, y;
	int *img_addr, *tex_addr;
	int bpp, line_len, endian;
	int tex_bpp, tex_line_len, tex_endian;
	int texture_width, texture_height;

	// Get the image address for the sky/floor base image
	img_addr = (int *)mlx_get_data_addr(sky_floor_img, &bpp, &line_len, &endian);

	// Get the image address for the selected texture
	tex_addr = (int *)mlx_get_data_addr(data->textureinfo[texture_idx]->img, &tex_bpp, &tex_line_len, &tex_endian);
	texture_width = data->textureinfo[texture_idx]->texture_width;
	texture_height = data->textureinfo[texture_idx]->texture_height;

	// Calculate new width and height for the texture (1/4 size of the window)
	int scaled_width = WIDTH / 2;
	int scaled_height = HEIGHT / 2;

	// Calculate the start position (centered in the window)
	int start_x = (WIDTH - scaled_width) / 2;
	int start_y = (HEIGHT - scaled_height) / 2;

	// Loop to render the scaled texture (1/4 size) on top of the sky/floor base
	for (y = 0; y < scaled_height; y++)
	{
		for (x = 0; x < scaled_width; x++)
		{
			// Calculate the corresponding texture coordinates (scaling down)
			int tex_x = (x * texture_width) / scaled_width;
			int tex_y = (y * texture_height) / scaled_height;

			// Ensure we are within bounds of the image buffer
			if ((start_x + x) >= 0 && (start_x + x) < WIDTH && (start_y + y) >= 0 && (start_y + y) < HEIGHT)
			{
				// Copy the scaled pixel from texture to background image buffer (sky/floor base)
				img_addr[(start_y + y) * (line_len / 4) + (start_x + x)] = tex_addr[tex_y * (tex_line_len / 4) + tex_x];
			}
		}
	}
}

int	clear_textures(t_data *data, char **path, int i)
{
	while (--i >= 0)
	{
		if (data->textureinfo[i])
		{
			if (data->textureinfo[i]->img)
				mlx_destroy_image(data->mlx_conn, data->textureinfo[i]->img);
			free(data->textureinfo[i]);
		}
	}
	free(path[i]);
	error_exit("ERROR: problems loading texture.\n", data, NULL);
	return (EXIT_FAILURE);
}

int	ft_init_textures(t_data *data)
{
	char            **path;
	// Set up paths for textures
	path = (char **)ft_calloc(5, sizeof(char *));
	if (!path)
		return (0);
	path[0] = "walls/temple.xpm";
	path[1] = "walls/pixgreen.xpm";
	path[2] = "walls/WE.xpm";
	path[3] = "walls/EA.xpm";
	path[4] = NULL;

	int i = 0;
	while (path[i])
	{
		data->textureinfo[i] = (t_img *)ft_calloc(1, sizeof(t_img));
		if (!data->textureinfo[i])
			return (clear_textures(data, path, i));
		data->textureinfo[i]->img = mlx_xpm_file_to_image(data->mlx_conn, path[i], \
			&data->textureinfo[i]->texture_width, &data->textureinfo[i]->texture_height);
		if (!data->textureinfo[i]->img)
			return (clear_textures(data, path, i));
		data->textureinfo[i]->img_addr = (int *)mlx_get_data_addr(data->textureinfo[i]->img,\
			&data->textureinfo[i]->bpp, &data->textureinfo[i]->line_len, &data->textureinfo[i]->endian);
		if (!data->textureinfo[i]->img_addr)
			return (clear_textures(data, path, i));
		i++;
	}
	free(path);
	return (EXIT_SUCCESS);
}

int main(void)
{
	t_data          *data;
	unsigned int    sky;
	unsigned int    floor;
	void            *sky_floor_img;

	// Set sky and floor colors
	sky = 0x87CEEB;   // Sky blue
	floor = 0x228B22; // Forest green

	// Allocate memory for the main data structure
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (0);
	data->mlx_conn = mlx_init();
	if (!data->mlx_conn)
	{
		free(data);
		return (0);
	}

	// Create a window
	data->mlx_window = mlx_new_window(data->mlx_conn, WIDTH, HEIGHT, "hi :)");
	if (!data->mlx_window)
	{
		mlx_destroy_display(data->mlx_conn);
		free(data->mlx_conn);
		free(data);
		return (0);
	}

	if (ft_init_textures(data) == EXIT_FAILURE)
	{
		printf("Error creating image for sky and floor base.\n");
		on_destroy(data);
		return (0);
	}
	// Create an off-screen image buffer to store the sky/floor base
	sky_floor_img = mlx_new_image(data->mlx_conn, WIDTH, HEIGHT);
	if (!sky_floor_img)
	{
		printf("Error creating image for sky and floor base.\n");
		on_destroy(data);
		return (0);
	}

	// Render the sky and floor once and store in the base image buffer
	render_sky_floor_base(sky, floor, sky_floor_img);

	// Use the stored sky/floor base and render a texture on top of it
	render_scaled_texture_on_base(data, 0, sky_floor_img);  // Renders the texture from path[0]

	// Display the composed image (sky/floor base + texture) to the window
	mlx_put_image_to_window(data->mlx_conn, data->mlx_window, sky_floor_img, 0, 0);

	// Set up the keypress hook
	mlx_hook(data->mlx_window, KeyRelease, KeyReleaseMask, &on_keypress, data);

	// Start the MinilibX event loop
	mlx_loop(data->mlx_conn);

	// Free resources at the end
	if (sky_floor_img)
		mlx_destroy_image(data->mlx_conn, sky_floor_img);
	
	on_destroy(data);

	return (0);
}
