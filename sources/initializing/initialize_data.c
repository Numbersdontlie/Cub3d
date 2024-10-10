/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:08:40 by luifer            #+#    #+#             */
/*   Updated: 2024/10/10 05:49:16 by kbolon           ###   ########.fr       */
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
	data->mapinfo = (t_mapinfo *)ft_calloc(1, sizeof(t_mapinfo));
	if (!data->mapinfo)
		return (error_message_simple("ERROR: problems init map\n", NULL));	
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
	return (EXIT_SUCCESS);
}

//Function to initialize the data struct so we can run our game eventually
int	ft_initialize_data(t_data **data, t_textinfo *text)
{
	*data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!*data)
		return (error_message_simple("ERROR: problems copying grid in init\n", NULL));
	(*data)->textinfo = text;
	if (ft_initialize_map(*data, text) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_initialize_player(*data) == EXIT_FAILURE)
		return (error_message_simple("ERROR: problems init player\n", NULL));
	return (EXIT_SUCCESS);
}

//Function to initialize the player structure
int	ft_initialize_player(t_data *data)
{
	int	x;
	int	y;

	ft_memset(&data->player, 0, sizeof(t_player));
	x = find_item(data->mapinfo->grid, 'x');
	y = find_item(data->mapinfo->grid, 'y');
	data->player.pos_x = x + 0.5;
	data->player.pos_y = y + 0.5;
	data->mapinfo->grid[y][x] = '0';
	if (check_player_position(data) == EXIT_FAILURE)
		return (error_message_simple("ERROR: problems player position\n", NULL));
	ft_init_player_dir(data);
	return (EXIT_SUCCESS);
}

//function checkt that the player position is legit
int	check_player_position(t_data *data)
{
	int	i;
	int	j;

	i = (int)data->player.pos_y;
	j = (int)data->player.pos_x;
	if (data->mapinfo->grid[i][j - 1] == '1' || data->mapinfo->grid[i][j + 1] == '1' || \
		data->mapinfo->grid[i - 1][j] == '1' || data->mapinfo->grid[i - 1][j] == '1')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
