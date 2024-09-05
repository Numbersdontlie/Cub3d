/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:08:40 by luifer            #+#    #+#             */
/*   Updated: 2024/09/05 16:49:00 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//Function to initialize the image structure
void	ft_initialize_img(t_img *img)
{
	img->img = NULL;
	img->img_addr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
}

//Function to initializ the ray structure
void	ft_initialize_ray(t_ray *ray)
{
	ray->camera_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->sidedistance_x = 0;
	ray->sidedistance_y = 0;
	ray->deltadistance_x = 0;
	ray->deltadistance_y = 0;
	ray->wall_distance = 0;
	ray->wall_x = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

//temp function to get the grid working for parse testing
t_mapinfo 	*ft_initialize_map(t_data *data, t_textinfo *text)
{
	t_mapinfo	*mapinfo;

	if (!data)
		return (NULL);
	mapinfo = (t_mapinfo *) ft_calloc (1, sizeof(t_mapinfo));
	if (!mapinfo)
		error_message_data("ERROR: calloc fail in map_init", data, text);
	mapinfo->grid = data->map;
	mapinfo->line_count = row_count(data->map);
	mapinfo->player_x = find_item(mapinfo->grid, 'x');
	mapinfo->player_y = find_item(mapinfo->grid, 'y');
	return (mapinfo);
}

//Function to initialize the global data of the program
t_data	*ft_initialize_data(t_textinfo *text)
{
	t_data		*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		error_message_text("ERROR: problems copying grid in init\n", text);
	data->window_height = HEIGHT;
	data->window_width = WIDTH;
	data->player = (t_player *)ft_calloc(1, sizeof(t_player));
	if (!data->player)
		error_message_data("ERROR: problems init player", data, text);
	data->map = text->grid;
	return (data);
}
