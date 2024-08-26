/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:08:40 by luifer            #+#    #+#             */
/*   Updated: 2024/08/26 13:10:32 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3D.h"

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
t_mapinfo 	*ft_initialize_map(char	*grid)
{
	t_mapinfo	*mapinfo;

	if (!grid)
		return (NULL);
	mapinfo = (t_mapinfo *) ft_calloc (1, sizeof(t_mapinfo));
	if (!mapinfo)
		error_message_simple("ERROR: calloc fail in map_init", &grid);
	mapinfo->grid = &grid;
	mapinfo->line_count = row_count(&grid);
	mapinfo->player_x = find_item(mapinfo->grid, 'x');
	printf("x: %zu\n", mapinfo->player_x);
	mapinfo->player_y = find_item(mapinfo->grid, 'y');
	return (mapinfo);
}

//Function to initialize the player structure
void	ft_initialize_player(t_player *player)
{
	player->direction = 0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->move_x = 0;
	player->move_y = 0;
	player->rotate = 0;
	player->has_moved = 0;
}

//Function to initialize the global data of the program
void	ft_initialize_data(t_data *data)
{
	data->mlx_conn = NULL;
	data->mlx_window = NULL;
	data->window_height = HEIGHT;
	data->window_width = WIDTH;
	ft_initialize_player(&data->player);
//	ft_initialize_textinfo(&data->textinfo);//ToDo
	data->map = NULL;
//	ft_initialize_map(&data->mapinfo);
	data->texture_pixels = NULL;
	data->textures = NULL;
}
