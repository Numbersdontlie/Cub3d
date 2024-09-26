/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:08:40 by luifer            #+#    #+#             */
/*   Updated: 2024/09/26 12:33:25 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//temp function to get the grid working for parse testing
void 	ft_initialize_map(t_data *data, t_textinfo *text)
{
	size_t		i;
	size_t		count;

	if (!data)
		return ;
	i = 0;
	data->mapinfo->line_count = row_count(text->grid);
	count = data->mapinfo->line_count;
	data->mapinfo->grid = (char **)ft_calloc (count + 1, sizeof(char *));
	if (!data->mapinfo->grid)
		error_exit("ERROR: calloc fail in map_init", data, text);
	while (i < count)
	{
		data->mapinfo->grid[i] = ft_strdup(text->grid[i]);
		if (!data->mapinfo->grid[i])
			error_exit("ERROR: ft_strdup fail in map_init", data, text);
		i++;
	}
	data->mapinfo->grid[i] = NULL;
	data->mapinfo->player_x = find_item(data->mapinfo->grid, 'x');
	data->mapinfo->player_y = find_item(data->mapinfo->grid, 'y');
}

//Function to initialize the global data of the program
int	ft_initialize_data(t_data **data, t_textinfo *text)
{
	*data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!*data)
		error_exit("ERROR: problems copying grid in init\n", NULL, text);
	(*data)->textinfo = text;
	(*data)->player = (t_player *)ft_calloc(1, sizeof(t_player));
	if (!(*data)->player)
		error_exit("ERROR: problems init player", *data, text);
	(*data)->ray = (t_ray *)ft_calloc(1, sizeof(t_ray));
	if (!(*data)->ray)
		error_exit("ERROR: problems init ray", *data, text);
	(*data)->mapinfo = (t_mapinfo *)ft_calloc(1, sizeof(t_mapinfo));
	if (!(*data)->mapinfo)
		error_exit("ERROR: problems init map", *data, text);
	ft_initialize_map(*data, text);
	return (EXIT_SUCCESS);
}

//Function to initialize the texture pixels for the renderization
//it checks if the textures are already used and free if necessary
//and then allocate memory for the textures pixels to be rendered
/*void	ft_initialize_texture_pixels(t_data *data)
{
	int	i;

	if (data->textures)
		free(data->textures);
	data->textures = ft_calloc(HEIGHT, sizeof(int *));
	if (!data->textures)
		error_exit("problems calloc texture_pixels\n", data, NULL);
	i = 0;
	while (i < HEIGHT)
	{
		data->textures[i] = ft_calloc(WIDTH, sizeof(int));
		if (!data->textures[i])
			error_exit("problems calloc texture_pixels\n", data, NULL);
		i++;
	}
}*/

void	ft_initialize_texture_pixels(t_data *data)
{
	int	i;

	if (data->texture_pixels)
		free(data->texture_pixels);
	data->texture_pixels = ft_calloc(HEIGHT + 1, sizeof * data->texture_pixels);
	if (!data->texture_pixels)
		ft_clean_exit(data);
	i = 0;
	while (i < HEIGHT)
	{
		data->texture_pixels[i] = ft_calloc(WIDTH + 1, sizeof * data->texture_pixels);
		if (!data->texture_pixels[i])
			ft_clean_exit(data);
		i++;
	}
}