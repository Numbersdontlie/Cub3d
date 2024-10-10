/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_raycasting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:29:32 by luifer            #+#    #+#             */
/*   Updated: 2024/10/10 11:58:36 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

//Function to initialize the raycast
//it will initialize the ray structure to zero and then assign
//values to camera, ray direction, ray position in map, and 
//distance to the nearest line in the x or y direction in grid (next neighbor)
//camera_x refers where the camera is (-1 for left, 0 for center, 1 for right)
//dir_x/y refers to the direction of the ray
//map_x/y refers to the current coordinates(x,y) in which the ray is 
//deltadist_x/y refers to the distance of the next x, y
void	ft_initialize_raycasting(int x, t_ray *ray, t_player *player)//init_raycasting_info
{
	memset(ray, 0, sizeof(t_ray));//ok tested with other code
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_y = (int)player->pos_y;
	ray->map_x = (int)player->pos_x;
	ray->deltadistance_x = fabs(1 / ray->dir_x);
	ray->deltadistance_y = fabs(1 / ray->dir_y);
}

//Function to calculate the step and initial side distances
//the step_x and step_y determine the direction in which the ray
//moves through the grid. The sidedist_x and y represents
//the dist the ray must travel from current position to next grid
//line in x or y direction
void	ft_get_ray_step_and_distance(t_ray *ray, t_player *player)//set_dda
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedistance_x = (player->pos_x - ray->map_x) \
			* ray->deltadistance_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedistance_x = (ray->map_x + 1.0 - player->pos_x) \
			* ray->deltadistance_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedistance_y = (player->pos_y - ray->map_y) \
			* ray->deltadistance_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedistance_y = (ray->map_y + 1.0 - player->pos_y) \
			* ray->deltadistance_y;
	}
}

//Function to perform DDA, it will determine the distance
//to the next grid line in the x or y direction. The player
//will move through the grid and calculate the distance to the next
//grid line in x and y (it also notes which side of the wall was hit x or y)
//sidedist refers to dist from player position to next x or y side of grid
//deltadis refers to how far ray moves in x or y direction when crossing a grid
//map_x/y refers to current position (x,y) of ray in map
//step_x/y refers to direction in which ray is moving (1 or -1)
void	ft_implement_dda(t_data *data, t_ray *ray)//perform_dda
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
			ray->map_y > data->mapinfo->map_height - 0.25 || \
			ray->map_x > data->mapinfo->map_width - 1.25)
			return ;
		else if (data->mapinfo->grid[ray->map_y][ray->map_x] > '0')//maybe we check if it's also a player
			return ;
	}
}

//Function to calculate how tall the wall height appears on the screen
//it calculates the wall distance based if the ray hit in a vertical 
//or horizontal wall (defined by ray->side)
//to the wall and them derive the draw start and end position.
void	ft_calculate_wall_height(t_ray *ray, t_data *data, t_player *player)//calculate_line_height
{
	if (ray->side == 0)
		ray->wall_distance = (ray->sidedistance_x - ray->deltadistance_x);
	else
		ray->wall_distance = (ray->sidedistance_y - ray->deltadistance_y);
	ray->line_height = (int)(data->height / ray->wall_distance);
	ray->draw_start = -(ray->line_height / 2) + (data->height / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + (data->height / 2);
	if (ray->draw_end >= data->height)
		ray->draw_end = data->height - 1;
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
	t_ray	ray;

	x = 0;
	ray = data->ray;
	while (x < data->width)
	{
		ft_initialize_raycasting(x, &ray, player);//init_raycasting_info
		ft_get_ray_step_and_distance(&ray, player);//set_dda
		ft_implement_dda(data, &ray);//perform_dda
		ft_calculate_wall_height(&ray, data, &data->player);//calculate_line_height
//		ft_get_texture_idx(data, &ray);
//		ft_calculate_texture_coordinates(data, &ray);
		ft_update_texture_pixels(data, &ray, x);//update_texture_pixels
		x++;
	}
	return (EXIT_SUCCESS);
}

void	ft_calculate_texture_coordinates(t_data *data, t_ray *ray)//part of update_texture_pixels
{
	data->textinfo->x = (int)(ray->wall_x * data->textinfo->size);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		data->textinfo->x = data->textinfo->size - data->textinfo->x - 1;
	data->textinfo->step = 1.0 * data->textinfo->size / ray->line_height;
	data->textinfo->pos = (ray->draw_start - data->height / 2 + \
		ray->line_height / 2) * data->textinfo->step;
}

//Function to update the texture pixels on the screen for render
//it calculates which part of the texture to apply to the current vertical line
//it flip the textures based on the direction the ray hits the wall
void	ft_update_texture_pixels(t_data *data, t_ray *ray, int x)//update_texture_pixels
{
	int		y;
	int		colour;

	ft_get_texture_idx(data, ray);
	ft_calculate_texture_coordinates(data, ray);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
//		data->textinfo->y = (int)data->textinfo->pos % PIXELS;
		data->textinfo->y = (int)data->textinfo->pos & (data->textinfo->size - 1);
		data->textinfo->pos += data->textinfo->step;
		colour = data->textures[data->textinfo->idx][data->textinfo->size * \
			data->textinfo->y + data->textinfo->x];
		if (data->textinfo->idx == N || data->textinfo->idx == E)
			colour = (colour >> 1);// & 8355711;
		if (colour > 0)
			data->texture_pixels[y][x] = colour;
		y++;
	}
}
