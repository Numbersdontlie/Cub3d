/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:08:40 by luifer            #+#    #+#             */
/*   Updated: 2024/10/08 12:11:09 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//function initializes the map struct and saves it in our data struct
int 	ft_initialize_map(t_data *data, t_textinfo *text)
{
	size_t		i;
	size_t		count;

	if (!data)
		return (error_message_simple("ERROR: data struct not init", NULL));
	i = 0;
	data->mapinfo->map_height = row_count(text->grid);
	count = data->mapinfo->map_height;
	data->mapinfo->grid = (char **)ft_calloc (count + 1, sizeof(char *));
	if (!data->mapinfo->grid)
		return (error_message_simple("ERROR: calloc fail in map_init", NULL));
	while (i < count)
	{
		data->mapinfo->grid[i] = ft_strdup(text->grid[i]);
		if (!data->mapinfo->grid[i])
			return (error_message_simple("ERROR: ft_strdup fail in map_init", NULL));
		i++;
	}
	data->mapinfo->grid[i] = NULL;
	data->mapinfo->player_x = find_item(data->mapinfo->grid, 'x');
	data->mapinfo->player_y = find_item(data->mapinfo->grid, 'y');
	return (EXIT_SUCCESS);
}

//Function to initialize the data struct so we can run our game eventually
int	ft_initialize_data(t_data **data, t_textinfo *text)
{
	*data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!*data)
		return (error_message_simple("ERROR: problems copying grid in init\n", NULL));
	(*data)->textinfo = text;
	(*data)->player = (t_player *)ft_calloc(1, sizeof(t_player));
	if (!(*data)->player)
		return (error_message_simple("ERROR: problems init player\n", NULL));
	(*data)->ray = (t_ray *)ft_calloc(1, sizeof(t_ray));
	if (!(*data)->ray)
		return (error_message_simple("ERROR: problems init ra\n", NULL));
	(*data)->mapinfo = (t_mapinfo *)ft_calloc(1, sizeof(t_mapinfo));
	if (!(*data)->mapinfo)
		return (error_message_simple("ERROR: problems init map\n", NULL));
	if (ft_initialize_map(*data, text) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_initialize_connection(*data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_initialize_textures(*data) == EXIT_FAILURE)
//	{
//		mlx_destroy_display((*data)->mlx_conn);
//		free((*data)->mlx_conn);
		return (EXIT_FAILURE);
//	}
	if (ft_init_background(*data) == EXIT_FAILURE)
//	{
//		if ((*data)->background.img)
//			mlx_destroy_window((*data)->mlx_conn, (*data)->background.img);
		return (EXIT_FAILURE);
//	}
	return (EXIT_SUCCESS);
}

//Function to try to initialize the mapinfo in a different way
//just for testing(all to zero)
void	ft_mapinfo_init(t_mapinfo *map)
{
	map->fd = 0;
	map->grid = NULL;
	map->map_height = 0;
	map->map_width = 0;
	map->idx_map_end = 0;
	
}

//Function to try to initialize the player in a different way
//just for testing (all to zero)
void	ft_player_init(t_player *player)
{
	player->direction = NULL;
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->has_moved = 0;
	player->move_x = 0;
	player->move_y = 0;
	player->rotate = 0;
}

//Function to try to initialize the player in a different way
//just for testing (all to zero)
void	ft_textinfo_init(t_textinfo *texture)
{
	texture->paths = NULL;
	texture->floor_rgb = 0;
	texture->ceiling_rgb = 0;
	texture->grid = NULL;
	texture->hex_floor = 0x0;
	texture->hex_ceiling = 0x0;
	texture->size = 0;
	texture->idx = 0;
	texture->step = 0.0;
	texture->pos = 0.0;
	texture->x = 0;
	texture->y = 0;
}

//Function to try to initialize the data in a different way
//just for testing
void	ft_data_init(t_data *data)
{
	data->mlx_conn = NULL;
	data->mlx_window = NULL;
	data->map = NULL;
	data->path = NULL;
	ft_mapinfo_init(data->mapinfo);
	ft_player_init(data->player);
	ft_textinfo_init(data->textinfo);
	data->text_pixels = NULL;
	data->textures = NULL;
}

/*
//function loads the sky and floor colours and creates a background image
//of the two colours.  We split it 50/50 for now. Function also checks
//the image was created and saves the address.
int	ft_init_background(t_data *data)
{
	data->background.img = mlx_new_image(data->mlx_conn, WIDTH, HEIGHT);
	if (!data->background.img)
		return (error_message_simple("ERROR: problem initiating background\n", NULL));
	data->background.img_addr = (int *)mlx_get_data_addr(data->background.img, \
			&data->background.bpp, &data->background.line_len, \
			&data->background.endian);
	if (!data->background.img_addr)
		return (error_message_simple("ERROR: problem getting background address\n", NULL));
	return (EXIT_SUCCESS);
}
*/