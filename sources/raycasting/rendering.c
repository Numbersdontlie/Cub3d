/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:56:52 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/25 16:12:33 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

//function loads the game image (renders floor and ceiling
//raycasts to render walls and displays final image)
int	ft_game(t_data *data)
{
	mlx_clear_window(data->mlx_conn, data->mlx_window);
	ft_render_ceiling_and_floor(data);
	ft_make_raycasting(data->player, data);
	mlx_put_image_to_window(data->mlx_conn, data->mlx_window, \
		data->imginfo->img, 0 , 0);
	return (0);
}

//function moves player forward and backword
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

//function moves player rotate left and right
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

//function splits the screen into two parts and 
//extracts colours for floor and ceiling
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
