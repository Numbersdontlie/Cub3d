/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:08:40 by luifer            #+#    #+#             */
/*   Updated: 2024/09/09 10:31:08 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
