/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:56:52 by kbolon            #+#    #+#             */
/*   Updated: 2024/10/02 14:29:30 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

//function loads the game image (renders floor and ceiling
//raycasts to render walls and displays final image)
int	ft_launch_game(t_data *data)
{
	render_sky_floor_base(data->textinfo->hex_ceiling, data->textinfo->hex_floor, data);

	//this function was only made to see if I could layer the images
	//FOR TESTING ONLY, change middle variable 0-3 to test the different tiles
	render_scaled_texture_on_base(data, 3, data->background.img);//TEST ONLY
//	ft_render(data);
	
//	ft_move_player(data);
	mlx_put_image_to_window(data->mlx_conn, data->mlx_window, data->background.img, 0, 0);

	return (EXIT_SUCCESS);
}

void	ft_put_pixel_to_img(t_img *imginfo, int x, int y, int colour)
{
	char	*pixel;

	if (!imginfo || !imginfo->img_addr)
		return ;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = (char *)imginfo->img_addr + (y * imginfo->line_len + x * \
		(imginfo->bpp/8));
	*(unsigned int *)pixel = colour;
}
//Function to render the game, it will check if the player
//has moved and update the player new position accordingly
//the raycast is render after this verification
int	ft_render(t_data *data)
{
	if (ft_move_player(data))
	{
		ft_make_raycasting(data->player, data);
		mlx_put_image_to_window(data->mlx_conn, data->mlx_window, data->background.img, 0, 0);
	}
	return (EXIT_SUCCESS);
}


/*function makes background image, top half is sky/ceiling and bottom half
is floor*/
void render_sky_floor_base(unsigned int sky, unsigned int floor, t_data *data)
{
	int x, y;
	int *img_addr;

	img_addr = data->background.img_addr;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				img_addr[y * (data->background.line_len / 4) + x] = sky;
			else
				img_addr[y * (data->background.line_len / 4) + x] = floor;
			x++;
		}
		y++;
	}
}


/*function should be removed, it was for testing only to see if I could render
a tile over the sky/floor background image*/
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