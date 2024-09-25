/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:49:35 by lperez-h          #+#    #+#             */
/*   Updated: 2024/09/25 15:09:23 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

//Function to get the texture index from the texture info struct
//if side is not zero, we're working on the y axis, else on the x
//if dir_y is greather than zero then we're on South 
//else North. If x axis is lower than zero is west else east
void	ft_get_texture_idx(t_data *data, t_ray *ray)
{
	if (ray->side == 1)
	{
		if (ray->dir_y > 0)
			data->textinfo->idx = S;
		else
			data->textinfo->idx = N;
	}
	else
	{
		if (ray->dir_x < 0)
			data->textinfo->idx = W;
		else
			data->textinfo->idx = E;
	}
}

//Function to update the texture pixels on the screen for render
//it calculates which part of the texture to apply to the current vertical line
//it flip the textures based on the direction the ray hits the wall
//it applies a shadow by applying a bitwise operation to darken textures based
//on the direction (north or east)
void	ft_update_texture(t_data *data, int *texture, t_ray *ray, int x)
{
	int	y;
	int	colour;

	ft_get_texture_idx(data, ray);
	data->textinfo->x = (int)(ray->wall_x * data->textinfo->size);
	if ((ray->side == 0 && ray->dir_x < 0) || \
		(ray->side == 1 && ray->dir_y > 0))
		data->textinfo->x = data->textinfo->size - data->textinfo->x - 1;
	data->textinfo->step = 1.0 * data->textinfo->size / ray->line_height;
	data->textinfo->pos = (ray->draw_start - HEIGHT / 2 + \
		ray->line_height / 2) * data->textinfo->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		data->textinfo->y = (int)data->textinfo->pos & (data->textinfo->size - 1);
		data->textinfo->pos += data->textinfo->step;
		colour = texture[data->textinfo->size * data->textinfo->y + data->textinfo->x];
		ft_put_pixel_to_img(data->imginfo, x, y, colour);
		y++;
	}
}
//function to render wall texture based on raycasting
void	ft_render_wall_texture(t_data *data, t_ray *ray, int x)
{
	int		y;
	int		colour;
	int		texture_x;
	int		texture_y;
	double	step;
	double	texture_pos;

	ft_get_texture_idx(data, ray);
	texture_x = (int)(ray->wall_x * (double)data->textinfo->size);
	if (ray->side == 0 && ray->dir_x > 0)
		texture_x = data->textinfo->size - texture_x - 1;
	step = 1.0 * data->textinfo->size/ray->line_height;
	texture_pos = (ray->draw_start - HEIGHT/2 + ray->line_height/2);
//renders texture line by line
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		texture_y = (int)texture_pos & (data->textinfo->size - 1);
		texture_pos += step;
		colour = data->textures[data->textinfo->idx][data->textinfo->size * texture_y + texture_x];
		ft_put_pixel_to_img(data->imginfo, x, y, colour);
		y++;
	}
}
