/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_raycasting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:29:32 by luifer            #+#    #+#             */
/*   Updated: 2024/09/09 10:30:42 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

//Function to initialize the raycast
//it will initialize the ray structure to zero and then assign
//values to camera, ray direction, ray position in map, and 
//distance to the nearest line in the x or y direction in grid (next neighbor)
void	ft_initialize_raycasting(int x, t_ray *ray, t_player *player)
{	
	ray = (t_ray *)ft_calloc(1, sizeof(t_ray));
	if (!ray)
		return (EXIT_FAILURE);
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
	int	contact;

	contact = 0;
	while (contact == 0)
	{
		if (ray->sidedistance_x < ray->sidedistance_y)
		{
			ray->sidedistance_x += ray->deltadistance_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedistance_y += ray->sidedistance_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0.25 || ray->map_x < 0.25 || ray->map_y > data->mapinfo.height - 0.25 || ray->map_x > data->mapinfo.width - 1.25)
			break ;
		else if (data->map[ray->map_y][ray->map_x] > '0')
			contact = 1;
	}
}

//Function to calculate the wall height based on the distance
//to the wall and the player's view angle. 1st we get the distance 
//to the wall and them derive the draw star and end position.
void	ft_calculate_wall_height(t_data *data, t_player *player, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_distance = (ray->sidedistance_x - ray->deltadistance_x);
	else
		ray->wall_distance = (ray->sidedistance_y - ray->deltadistance_y);
	ray->line_height = (int)(data->window_height / ray->wall_distance);
	ray->draw_start = -(ray->line_height / 2) + (data->window_height / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + (data->window_height / 2);
	if (ray->draw_end >= data->window_height)
		ray->draw_end = data->window_height - 1;
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->wall_distance * ray->dir_y;
	else
		ray->wall_x = player->pos_x + ray->wall_distance * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

//Function to make the raycasting works
//It will iterate through the width of screen and update
//the data to render the ray from the current position and
//point of view of the player
int	ft_make_raycasting(t_player *player, t_data *data)
{
	t_ray	*ray;
	int		x;

	x = 0;
	ray = &data->ray;
	while (x < data->window_width)
	{
		ft_initialize_raycasting(x, ray, player);
		ft_get_ray_step_and_distance(ray, player);
		ft_implement_dda(data, ray);
		ft_calculate_wall_height(data, player, ray);
		ft_update_texture_pixels(data, data->textinfo, ray, x);
		x++;
	}
	return (EXIT_SUCCESS);
}
