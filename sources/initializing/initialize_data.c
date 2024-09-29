/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:08:40 by luifer            #+#    #+#             */
/*   Updated: 2024/09/29 10:58:48 by kbolon           ###   ########.fr       */
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
	data->mapinfo->map_height = row_count(text->grid);
	count = data->mapinfo->map_height;
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

int	ft_initialize(t_data *data, t_textinfo *text)
{
	if (ft_initialize_connection(data, text) == EXIT_FAILURE)
	{
		error_exit("ERROR: problem initiating connection\n", data, text);
		return (EXIT_FAILURE);
	}
	if (ft_initialize_textures(data, text) == EXIT_FAILURE)
	{
		error_exit("ERROR: problem initiating textures\n", data, text);
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
int	ft_init_background(t_data *data, t_textinfo *text)
{
	data->background.img = mlx_new_image(data->mlx_conn, WIDTH, HEIGHT);
	if (!data->background.img)
	{
		error_exit("ERROR: problem initiating background\n", data, text);
		return (EXIT_FAILURE);
	}
	data->background.img_addr = (int *)mlx_get_data_addr(data->background.img, \
			&data->background.bpp, &data->background.line_len, \
			&data->background.endian);
	if (!data->background.img_addr)
	{
		error_exit("ERROR: problem getting background address\n", data, text);
		return (EXIT_FAILURE);
	}
	ft_render_background(data);
	return (EXIT_SUCCESS);
}
