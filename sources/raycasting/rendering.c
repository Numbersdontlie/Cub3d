/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:56:52 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/18 16:53:13 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

int	ft_game(t_data *data)
{
	if (!data || !data->mapinfo || !data->imginfo->img)
		error_message("ERROR: imginfo or img not initialized\n");
	mlx_clear_window(data->mlx_conn, data->mlx_window);
	ft_make_raycasting(data->player, data);
	ft_player_movement_forward_backword(data);
	ft_rotation(data);
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
