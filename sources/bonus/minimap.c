/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:08:50 by kbolon            #+#    #+#             */
/*   Updated: 2024/10/17 13:12:23 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

int	ft_mouse_handler(t_data *data, int x, int y)
{
//	if (!data || !data->mlx_conn || !data->mlx_conn)
//		return (0);
	ft_mouse_position(data, x, y);
	if (x == WIDTH / 2)
		return (0);
	else if (x < WIDTH / 2)
		data->player.has_moved += ft_execute_rotation(data, -1);
	else if (x > WIDTH / 2)
		data->player.has_moved += ft_execute_rotation(data, 1);
	return (0);
}

void	ft_mouse_position(t_data *data, int x, int y)
{
	if (x > data->width - MOUSE)
	{
		x = MOUSE;
		mlx_mouse_move(data->mlx_conn, data->mlx_window, x, y);
	}
	else if (x < MOUSE)
	{
		x = data->width - MOUSE;
		mlx_mouse_move(data->mlx_conn, data->mlx_window, x, y);
	}
}

//initialize minimap struct
void	ft_initialize_minimap(t_data *data)
{
	data->minimap.tile_size = 10;
	data->minimap.width = data->mapinfo->map_width * data->minimap.tile_size;
	data->minimap.height = data->mapinfo->map_height * data->minimap.tile_size;
	data->minimap.mini_x = 10;
	data->minimap.mini_y = data->height - data->minimap.height - 10;
}

void	render_minimap(t_data *data)
{
	int		x;
	int		y;
	t_img	image;

	ft_initialize_minimap(data);
	image.img = mlx_new_image(data->mlx_conn, \
		data->minimap.width, data->minimap.height);
	image.img_addr = (int *)mlx_get_data_addr(image.img, \
		&image.bpp, &image.line_len, &image.endian);
	y = 0;
	while (y < (int)data->mapinfo->map_height)
	{
		x = 0;
		while (x < (int)data->mapinfo->map_width)
		{
			ft_make_mini_tiles(data, &image, y, x);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_conn, data->mlx_window, image.img,\
		data->minimap.mini_x, data->minimap.mini_y);
	mlx_destroy_image(data->mlx_conn, image.img);
}

