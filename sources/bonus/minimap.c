/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:08:50 by kbolon            #+#    #+#             */
/*   Updated: 2024/10/07 10:59:33 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

int	ft_launch_game_bonus(t_data *data)
{
	render_sky_floor_base(data->textinfo->hex_ceiling, data->textinfo->hex_floor, data);

	//this function was only made to see if I could layer the images
	//FOR TESTING ONLY, change middle variable 0-3 to test the different tiles
	render_scaled_texture_on_base(data, 3, data->background.img);//TEST ONLY
	mlx_put_image_to_window(data->mlx_conn, data->mlx_window, data->background.img, 0, 0);
	render_map_bonus(data);
	
//	ft_move_player(data);

	return (EXIT_SUCCESS);
}

void	ft_init_bonus(t_data *data)
{
	(*data)->bonus = 1;
}

void ft_init_minimap(t_data *data)
{
	(*data)->minimap = (t_mini *)ft_calloc (1, sizeof(t_mini));
	if (!(*data)->minimap)
		return (EXIT_FAILURE);
	(*data)->minimap->img = (t_img) * ft_calloc (1, sizeof(t_img));
	if (!(*data)->minimap->img)
		return (EXIT_FAILURE);
}
void	make_tiles(t_data *data, int x, int y, int colour)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;

	// Mini-map tile size
	int tile_size = MINI / 2;

	// Calculate starting positions
	start_x = x * tile_size;
	start_y = HEIGHT - (data->mapinfo->map_height * tile_size) + (y * tile_size);

	// Loop to draw the mini-map tile onto the image buffer
	for (i = 0; i < tile_size; i++)   // Vertical loop
	{
		for (j = 0; j < tile_size; j++)  // Horizontal loop
		{
			// Ensure we're within bounds of the image
			if ((start_x + i) < WIDTH && (start_y + j) < HEIGHT)
			{
				// Draw directly onto the image buffer
				img_addr[(start_y + j) * (line_len / 4) + (start_x + i)] = colour;
			}
		}
	}
}




void	render_map_bonus(t_data *data)
{
	int	i;
	int	j;
	int	*img_addr;
	int	line_len;
	int	bpp;
	int	endian;

	// Create an off-screen image for the mini-map
	void *mini_map_img = mlx_new_image(data->mlx_conn, WIDTH, HEIGHT);
	img_addr = (int *)mlx_get_data_addr(mini_map_img, &bpp, &line_len, &endian);

	// Iterate through the map grid and render each tile on the mini-map image
	i = 0;
	while (data->mapinfo->grid[i])
	{
		j = 0;
		while (data->mapinfo->grid[i][j])
		{
			if (data->mapinfo->grid[i][j] == '1')          // Wall
				make_tiles_on_image(data, j, i, WHITE, img_addr, line_len);
			else if (data->mapinfo->grid[i][j] == 'N' ||   // Player start position
			         data->mapinfo->grid[i][j] == 'E' ||
			         data->mapinfo->grid[i][j] == 'S' ||
			         data->mapinfo->grid[i][j] == 'W')
				make_tiles_on_image(data, j, i, RED, img_addr, line_len);
			else                                          // Empty spaces
				make_tiles_on_image(data, j, i, BLACK, img_addr, line_len);
			j++;
		}
		i++;
	}

	// Draw the player's current position on the mini-map
	make_tiles_on_image(data, data->player->pos_x, data->player->pos_y, RED, img_addr, line_len);

	// Display the mini-map in the window
	mlx_put_image_to_window(data->mlx_conn, data->mlx_window, mini_map_img, 0, 0);

	// Destroy the image to free up memory
	mlx_destroy_image(data->mlx_conn, mini_map_img);
}
