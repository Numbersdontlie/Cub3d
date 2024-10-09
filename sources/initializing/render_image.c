/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:56:52 by kbolon            #+#    #+#             */
/*   Updated: 2024/10/09 12:27:55 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

void	ft_init_game(t_data *data)
{
	ft_init_texture_pixels(data);
	ft_memset(data->ray, 0, sizeof(t_ray));
	ft_make_raycasting(data->player, data);
	ft_draw_image_in_window(data);
}

//not ours, from mcombeau
void	ft_init_texture_pixels(t_data *data)
{
	int	i;

	if (data->texture_pixels)
		free_textures(data->texture_pixels);
	data->texture_pixels = ft_calloc(HEIGHT + 1, sizeof(int *));
	if (!data->texture_pixels)
		error_exit("ERROR: calloc init texture pixels total\n", data, NULL);
	i = 0;
	while (i < HEIGHT)
	{
		data->texture_pixels[i] = ft_calloc(WIDTH + 1, sizeof(int));
		if (!data->texture_pixels[i])
			error_exit("ERROR: calloc init texture pixels\n", data, NULL);
		i++;
	}
}

void	ft_put_pixel_to_img(t_img *imginfo, int x, int y, int colour)
{
	int	*pixel;

	if (x< 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = (int *)((char *)imginfo->img_addr + (y * imginfo->line_len) + (x * (imginfo->bpp / 8)));
	*pixel = colour;
}

//Function to render the game, it will check if the player
//has moved and update the player new position accordingly
//the raycast is render after this verification
int	ft_render(t_data *data)
{
	data->player->has_moved += ft_move_player(data);
	if (data->player->has_moved == 0)
		return (EXIT_SUCCESS);
	ft_init_game(data);
	return (EXIT_SUCCESS);
}

//Function to update individual pixels in an image based on conditions
//it checks if texture pixels exits and set that pixel in the image to the 
//corresponding texture color in x and y. It also check if pixel is in ceiling or floor
//region and draw the ceiling or floor color if no texture is present
void	ft_update_pixels_img(t_data *data, t_img *img, int x, int y)
{
	if (data->texture_pixels[y][x] > 0)
		ft_put_pixel_to_img(img, x, y, data->texture_pixels[y][x]);
	else if (y < HEIGHT / 2)
		ft_put_pixel_to_img(img, x, y, data->textinfo->hex_ceiling);
	else if (y < HEIGHT - 1)
		ft_put_pixel_to_img(img, x, y, data->textinfo->hex_floor);
}

//Function to render an image into a window
//it will initialize an image buffer and fill it pixel by pixel
//setting the appropiate color for each point (x, y). After the buffer is full
//it display the whole buffer in the window and destroy the buffer and free memory
void	ft_draw_image_in_window(t_data *data)
{
	t_img	image;
	int		x;
	int		y;

	image.img = NULL;
	ft_init_img(data, &image);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_update_pixels_img(data, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_conn, data->mlx_window, image.img, 0, 0);
	mlx_destroy_image(data->mlx_conn, image.img);
}

//Function to render the ray structure of the game
//it will initialize the texture pixels, implement the raycasting
//algorithm and draw the resulting image in the window
void	ft_render_ray(t_data *data)
{
	ft_initialize_textures(data);
	ft_make_raycasting(data->player, data);
	ft_draw_image_in_window(data);
}
