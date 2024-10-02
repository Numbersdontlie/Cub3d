/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:08:50 by kbolon            #+#    #+#             */
/*   Updated: 2024/10/02 16:56:09 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

/*int	ft_launch_game_bonus(t_data *data)
{
	render_sky_floor_base_bonus(data->textinfo->hex_ceiling, data->textinfo->hex_floor, data);

	//this function was only made to see if I could layer the images
	//FOR TESTING ONLY, change middle variable 0-3 to test the different tiles
	render_scaled_texture_on_base_bonus(data, 3, data->background.img);//TEST ONLY
	ft_render_map_bonus(data);
	
//	ft_move_player(data);
	mlx_put_image_to_window(data->mlx_conn, data->mlx_window, data->background.img, 0, 0);

	return (EXIT_SUCCESS);
}

void	make_tiles(t_data *data, int x, int y, int colour)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;

	i = 0;
	start_x = x * MINI/4;
	start_y = HEIGHT * 0.75 + y * MINI/4;
	while (i < MINI / 4)
	{
		j = 0;
		while (j < MINI / 4)
		{
			mlx_pixel_put(data->mlx_conn, data->mlx_window, start_x + i, start_y + j, colour);
			j++;
		}
		i++;
	}
}

void	render_map_bonus(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->mapinfo->grid[i])
	{
		j = 0;
		while (data->mapinfo->grid[i][j])
		{
			if (data->mapinfo->grid[i][j] == '1')
				make_tiles(data, j, i, WHITE);
			else if (data->mapinfo->grid[i][j] == 'N' || data->mapinfo->grid[i][j] == 'E' ||\
				data->mapinfo->grid[i][j] == 'S' || data->mapinfo->grid[i][j] == 'W')
				make_tiles(data, j, i, RED);
			else
				make_tiles(data, j, i, BLACK);
			j++;
		}
		i++;
	}
	render_player_direction_bonus(data);
}
void render_sky_floor_base_bonus(unsigned int sky, unsigned int floor, t_data *data)
{
	int x, y;
	int *img_addr;

	img_addr = data->background.img_addr;
	y = 0;
	while (y < HEIGHT * 0.75)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < (HEIGHT * 0.75)/ 2)
				img_addr[y * (data->background.line_len / 4) + x] = sky;
			else
				img_addr[y * (data->background.line_len / 4) + x] = floor;
			x++;
		}
		y++;
	}
}

void render_scaled_texture_on_base_bonus(t_data *data, int texture_idx, void *sky_floor_img)
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
	int scaled_height = HEIGHT * 0.25 / 2;

	// Calculate the start position (centered in the window)
	int start_x = (WIDTH - scaled_width) / 2;
	int start_y = ((HEIGHT * 0.25) - scaled_height) / 2;

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

void	render_player_direction(t_data *data)
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;

	start_x = data->player->pos_x * (MINI / 4);
	start_y = HEIGHT * 0.75 + data->player->pos_y * (MINI / 4);
	end_x = start_x;
	end_y = start_y;
	if (data->player->direction == 'N')
		end_y -= 10;
	else if (data->player->direction == 'S')
		end_y += 10;
	else if (data->player->direction == 'E')
		end_y += 10;
	else if (data->player->direction == 'W')
		end_y -= 10;
	ft_draw_line(data, start_x, start_y, end_x, end_y, RED);
}

void	draw_line_for_player_direction(t_data *data, int x, int y, char dir)
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;

	start_x = x * (MINI / 4) + (MINI / 8);
	start_y = HEIGHT * 0.75  + y * (MINI / 4) + (MINI / 8);
	end_x = start_x;
	end_y = start_y;
	if (dir == 'N')
		end_y -= MINI / 4;
	else if (dir == 'S')
		end_y += MINI / 4;
	else if (dir == 'E')
		end_y += MINI / 4;
	else if (dir == 'W')
		end_y -= MINI / 4;
	draw_line(data, start_x, start_y, end_x, end_y);
}

void draw_line(t_data *data, int x0, int y0, int x1, int y1)
{
    int dx, dy, err, sx, sy;  // 5 variables total

    dx = abs(x1 - x0);  // Difference in x
    dy = abs(y1 - y0);  // Difference in y
    sx = (x0 < x1) ? 1 : -1;  // Direction for x (positive or negative)
    sy = (y0 < y1) ? 1 : -1;  // Direction for y (positive or negative)
    err = dx - dy;  // Error term

    while (1)
    {
        mlx_pixel_put(data->mlx_conn, data->mlx_window, x0, y0, RED);  // Draw pixel

        if (x0 == x1 && y0 == y1)  // Stop when we reach the end point
            break;

        if (2 * err > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (2 * err < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}*/