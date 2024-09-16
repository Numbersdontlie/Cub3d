/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:08:40 by luifer            #+#    #+#             */
/*   Updated: 2024/09/16 16:23:31 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//temp function to get the grid working for parse testing
void 	ft_initialize_map(t_data *data)
{
	t_mapinfo	*mapinfo;
	size_t		i;

	if (!data)
		return ;
	i = 0;
	mapinfo = (t_mapinfo *) ft_calloc (1, sizeof(t_mapinfo));
	if (!mapinfo)
		error_message_data("ERROR: calloc fail in map_init", data, NULL);
	mapinfo->line_count = row_count(data->map);
	mapinfo->grid = ft_calloc (mapinfo->line_count + 1, sizeof(char *));
	if (!mapinfo->grid)
		error_message_data("ERROR: calloc fail in map_init", data, NULL);
	while (i < mapinfo->line_count)
	{
		mapinfo->grid[i] = ft_strdup(data->map[i]);
		if (!mapinfo->grid[i])
			error_message_data("ERROR: ft_strdup fail in map_init", data, NULL);
		i++;
	}
	mapinfo->grid[i] = NULL;
	mapinfo->player_x = find_item(mapinfo->grid, 'x');
	mapinfo->player_y = find_item(mapinfo->grid, 'y');
	data->mapinfo = mapinfo;
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
	data->image_height = PIXELS;
	data->image_width = PIXELS;
	data->textinfo = text;
	data->player = (t_player *)ft_calloc(1, sizeof(t_player));
	if (!data->player)
		error_message_data("ERROR: problems init player", data, text);
	data->map = text->grid;
	ft_initialize_map(data);
	if (!data->map)
		error_message_data("ERROR: problems copying grid in init\n", data, text);
	return (data);
}

//Function to initialize the texture pixels for the renderization
//it checks if the textures are already used and free if necessary
//and then allocate memory for the textures pixels to be rendered
void	ft_initialize_texture_pixels(t_data *data)
{
	int	i;

	if (data->texture_pixels)
		free_pixels(data);
	data->texture_pixels = ft_calloc(data->window_height + 1, \
		sizeof * data->texture_pixels);
	if (!data->texture_pixels)
		error_message_data("problems calloc texture_pixels\n", data, NULL);
	i = 0;
	while (i < data->window_height)
	{
		data->texture_pixels[i] = ft_calloc(data->window_width + 1, \
			sizeof * data->texture_pixels);
		if (!data->texture_pixels)
			error_message_data("problems calloc texture_pixels\n", data, NULL);
		i++;
	}
}