/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderV2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:25:59 by luifer            #+#    #+#             */
/*   Updated: 2024/09/24 10:18:18 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

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
	t_img	*img;
	int		x;
	int		y;

//	img->img = NULL;
	img = ft_calloc(1, sizeof(t_img));
	ft_initialize_imginfo(data);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_update_pixels_img(data, img, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_conn, data->mlx_window, img->img, 0, 0);
	mlx_destroy_image(data->mlx_conn, img->img);
	free(img);
}

void	ft_render_ray(t_data *data)
{
	ft_initialize_texture_pixels(data);
	ft_make_raycasting(data->player, data);
	ft_draw_image_in_window(data);
}