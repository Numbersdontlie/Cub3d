/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_raycasting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:29:32 by luifer            #+#    #+#             */
/*   Updated: 2024/09/27 13:33:03 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

//Function to initialize the raycast
//it will initialize the ray structure to zero and then assign
//values to camera, ray direction, ray position in map, and 
//distance to the nearest line in the x or y direction in grid (next neighbor)
void	ft_initialize_raycasting(int x, t_ray *ray, t_player *player)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->map_y = (int)player->pos_y;
	ray->map_x = (int)player->pos_x;
	ray->deltadistance_y = fabs(1 / ray->dir_y);
	ray->deltadistance_x = fabs(1 / ray->dir_x);
}

//Function to calculate the step and initial side distances
//the step_x and step_y determine the direction in which the ray
//moves through the grid. The sidedist_x and y represents
//the dist the ray must travel from current position to next grid
//line in x or y direction
void	ft_get_ray_step_and_distance(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedistance_x = (player->pos_x - ray->map_x) * ray->deltadistance_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedistance_x = (ray->map_x + 1.0 - player->pos_x) * ray->deltadistance_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedistance_y = (player->pos_y - ray->map_y) * ray->deltadistance_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedistance_y = (ray->map_y + 1.0 - player->pos_y) * ray->deltadistance_y;
	}
}

//Function to perform DDA, it will determine the distance
//to the next grid line in the x or y direction. The player
//will move through the grid and calculate the distance to the next
//grid line in x and y (it also notes which side of the wall was hit x or y)
void	ft_implement_dda(t_data *data, t_ray *ray)
{
	while (1)
	{
		if (ray->sidedistance_x < ray->sidedistance_y)
		{
			ray->sidedistance_x += ray->deltadistance_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedistance_y += ray->deltadistance_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0.25 || ray->map_x < 0.25 || \
			ray->map_y > HEIGHT - 0.25 || \
			ray->map_x > WIDTH - 1.25)
			return ;
		if (data->mapinfo->grid[ray->map_y][ray->map_x] > '0')
			return ;
	}
}

//Function to calculate how tall the wall height appears on the screen
//it calculates the wall distance based if the ray hit in a vertical 
//or horizontal wall (defined by ray->side)
//to the wall and them derive the draw start and end position.
void	ft_calculate_wall_height(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->wall_distance = (ray->sidedistance_x - ray->deltadistance_x);
	else
		ray->wall_distance = (ray->sidedistance_y - ray->deltadistance_y);
	ray->line_height = (int)(HEIGHT / ray->wall_distance);
	ray->draw_start = -(ray->line_height / 2) + (HEIGHT / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + (HEIGHT / 2);
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->wall_distance * ray->dir_y;
	else
		ray->wall_x = player->pos_x + ray->wall_distance * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}


//Function to make the raycasting.  It iterates through the width of 
//screen and update the data to render the ray from the current position 
//and point of view of the player
//initializes ray, calculates steps and distances, performs DDA, 
//calculates wall height and updates textures
int	ft_make_raycasting(t_player *player, t_data *data)
{
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		ft_initialize_raycasting(x, data->ray, player);
		ft_get_ray_step_and_distance(data->ray, player);
		ft_implement_dda(data, data->ray);
		ft_calculate_wall_height(data->ray, data->player);
		ft_get_texture_idx(data, data->ray);
		ft_calculate_texture_coordinates(data, data->ray);
		ft_render_texture(data, (int *)data->imginfo[data->textinfo->idx], data->ray, x);
		x++;
	}
	return (EXIT_SUCCESS);
}

//this calculates the coordinate for the texture and adjusts for perspective
//while loop is a vertical slice of the image
/*void ft_render_texture(t_data *data, int *texture, t_ray *ray, int x)
{
	int y;
	int texture_x;
	int texture_y;
	int colour;

	texture_x = (int)(ray->wall_x * (double)data->imginfo[data->textinfo->idx]->texture_width);
	if (ray->side == 0 && ray->dir_x > 0)
		texture_x = data->imginfo[data->textinfo->idx]->texture_width - texture_x - 1;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		texture_y = (((y * 2 - HEIGHT + ray->line_height) * data->imginfo[data->textinfo->idx]->texture_height) / ray->line_height) / 2;
		colour = texture[texture_y * data->imginfo[data->textinfo->idx]->texture_width + texture_x];
		ft_put_pixel_to_img(data->imginfo[data->textinfo->idx], x, y, colour);
		y++;
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
		ft_put_pixel_to_img(data->imginfo[data->textinfo->idx], x, y, colour);
		y++;
	}
}*/

void	ft_calculate_texture_coordinates(t_data *data, t_ray *ray)
{
	data->textinfo->x = (int)(ray->wall_x *data->textinfo->size);
	if ((ray->side == 0 && ray->dir_x < 0) || \
		(ray->side == 1 && ray->dir_y > 0))
	data->textinfo->step = 1.0 * data->textinfo->size / ray->line_height;
	data->textinfo->pos = (ray->draw_start - HEIGHT / 2 + \
		ray->line_height / 2) * data->textinfo->step;
}

//this function draws the texture on the screen making sure it stays within the
//calculated coordinates of the texture
void ft_render_texture(t_data *data, int *texture, t_ray *ray, int x)
{
	int y;
	int texture_x;
	int texture_y;
	int colour;

	texture_x = data->textinfo->x;
		texture_x = data->imginfo[data->textinfo->idx]->texture_width - texture_x - 1;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		texture_y = (int)data->textinfo->pos % data->textinfo->size;
		data->textinfo->pos += data->textinfo->step;
		colour = texture[texture_y * data->textinfo->size + texture_x];
		ft_put_pixel_to_img(data->imginfo[data->textinfo->idx], x, y, colour);
		y++;
	}
}
