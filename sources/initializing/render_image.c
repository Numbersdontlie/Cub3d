/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:56:52 by kbolon            #+#    #+#             */
/*   Updated: 2024/10/07 21:45:56 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

void	ft_init_game(t_data *data)
{
//	data->background.img = mlx_new_image(data->mlx_conn, WIDTH, HEIGHT);
//	if (!data->background.img)
//		error_message("ERROR: Failed to create background image\n");
//	data->background.img_addr = (int *)mlx_get_data_addr(data->background.img, \
//		&data->background.bpp, &data->background.line_len, &data->background.endian);
//	if (!data->background.img_addr)
//		error_message("ERROR: Failed to get background image address\n");
	render_sky_floor_base(data->textinfo->hex_ceiling, data->textinfo->hex_floor, data);
	ft_initialize_imginfo(data);
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
		ft_draw_image_in_window(data);
		ft_make_raycasting(data->player, data);
		mlx_put_image_to_window(data->mlx_conn, data->mlx_window, data->imginfo->img, 0, 0);
	}
	return (EXIT_SUCCESS);
}

/*function makes background image, top half is sky/ceiling and bottom half
is floor*/
void render_sky_floor_base(unsigned int sky, unsigned int floor, t_data *data)
{
	int	x;
	int	y;
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

//Function to update individual pixels in an image based on conditions
//it checks if texture pixels exits and set that pixel in the image to the 
//corresponding texture color in x and y. It also check if pixel is in ceiling or floor
//region and draw the ceiling or floor color if no texture is present
void	ft_update_pixels_img(t_data *data, t_img *img, int x, int y)
{
	int	*texture_pix;
	int	pix;
	int	tex_x;
	int	tex_y;

	if (data->textinfo->idx < 0 || data->textinfo->idx > 3)
		return ;
	tex_x = x % data->textureinfo[data->textinfo->idx]->texture_width;
	tex_y = y % data->textureinfo[data->textinfo->idx]->texture_height;
	texture_pix = data->textureinfo[data->textinfo->idx]->img_addr;
	pix = texture_pix[tex_y * (data->textureinfo[data->textinfo->idx]->line_len / 4) + tex_x];
	if (pix > 0)
		ft_put_pixel_to_img(img, x, y, pix);
	else if (y < HEIGHT / 2)
		ft_put_pixel_to_img(img, x, y, data->textinfo->hex_ceiling);
	else if (y < HEIGHT - 1)
		ft_put_pixel_to_img(img, x, y, data->textinfo->hex_floor);
}

//Function to initialize the image, it will initialize an empty image structure
//create the new image using the mlx library and check that was correctly created
//assign the image address
int	ft_initialize_imginfo(t_data *data)
{
	if (!data->imginfo)
	{
		data->imginfo = (t_img *)ft_calloc(1, sizeof(t_img));
		if (!data->imginfo)
			error_message("ERROR: Failed to allocate imginfo\n");
	}
	if (data->imginfo && data->imginfo->img)
		mlx_destroy_image(data->mlx_conn, data->imginfo);
	data->imginfo->img = mlx_new_image(data->mlx_conn, WIDTH, HEIGHT);
	if (!data->imginfo->img)
		error_message("ERROR: failed to create image\n");
	data->imginfo->img_addr = (int *)mlx_get_data_addr(data->imginfo->img, \
		&data->imginfo->bpp, &data->imginfo->line_len, &data->imginfo->endian);
	if (!data->imginfo->img_addr)
		error_message("ERROR: failed to get img address\n");
	return (EXIT_SUCCESS);
}

//Function to render an image into a window
//it will initialize an image buffer and fill it pixel by pixel
//setting the appropiate color for each point (x, y). After the buffer is full
//it display the whole buffer in the window and destroy the buffer and free memory
void	ft_draw_image_in_window(t_data *data)
{
	int		x;
	int		y;

	if (!data->imginfo || !data->background.img)
	{
		ft_initialize_imginfo(data);
		return ;
	}
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_update_pixels_img(data, &data->background, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_conn, data->mlx_window, data->background.img, 0, 0);
//	mlx_destroy_image(data->mlx_conn, data->background.img);
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
