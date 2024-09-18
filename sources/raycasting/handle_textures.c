/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:49:35 by lperez-h          #+#    #+#             */
/*   Updated: 2024/09/18 13:34:52 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

//Function to get the texture index from the texture info struct
//if side is not zero, we're working on the y axis, else on the x
//if dir_y is greather than zero then we're on South 
//else North. If x axis is lower than zero is west else east
void	ft_get_texture_idx(t_data *data, t_ray *ray)
{
	if (ray->side != 0)
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
void	ft_update_texture(t_data *data, t_textinfo *texture, t_ray *ray, int x)
{
	int	y;
	int	color;

	ft_get_texture_idx(data, ray);
	texture->x = (int)(ray->wall_x * texture->size);
	if ((ray->side == 0 && ray->dir_x < 0) || \
		(ray->side == 1 && ray->dir_y > 0))
		texture->x = texture->size - texture->x - 1;
	texture->step = 1.0 * texture->size / ray->line_height;
	texture->position = (ray->draw_start - HEIGHT / 2 + \
		ray->line_height / 2) * texture->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		texture->x = (int)texture->position & (texture->size - 1);
		texture->position += texture->step;
		color = data->texture_pixels[texture->idx][texture->size \
			* texture->y + texture->x];
		if (texture->idx == N || texture->idx == E)
			color = (color >> 1) & RED;
		if (color > 0)
			data->texture_pixels[y][x] = color;
		y++;
	}
}
