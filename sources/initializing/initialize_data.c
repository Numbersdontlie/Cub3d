/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:08:40 by luifer            #+#    #+#             */
/*   Updated: 2024/10/09 16:32:16 by kbolon           ###   ########.fr       */
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
	ft_initialize_player(&(*data)->player);
//	(*data)->ray = (t_ray *)ft_calloc(1, sizeof(t_ray));
//	if (!(*data)->ray)
//		return (error_message_simple("ERROR: problems init ra\n", NULL));
	(*data)->mapinfo = (t_mapinfo *)ft_calloc(1, sizeof(t_mapinfo));
	if (!(*data)->mapinfo)
		return (error_message_simple("ERROR: problems init map\n", NULL));
	if (ft_initialize_map(*data, text) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_init_player_dir(*data);//initialize player data
	return (EXIT_SUCCESS);
}


/*void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
	init_player(&data->player);
	init_texinfo(&data->texinfo);
	data->map = NULL;
//	init_mapinfo(&data->mapinfo);
	data->mapinfo = (t_mapinfo *)ft_calloc(1, sizeof(t_mapinfo));
	if (!data->mapinfo)
		return (error_message_simple("ERROR: problems init map\n", NULL));
	if (ft_initialize_map(data, text) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	data->texture_pixels = NULL;
	data->textures = NULL;
}*/

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

