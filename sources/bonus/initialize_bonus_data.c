/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bonus_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:08:40 by luifer            #+#    #+#             */
/*   Updated: 2024/10/07 11:25:29 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//function initializes the map struct and saves it in our data struct
int 	ft_initialize_map(t_data *data, t_textinfo *text)
{
	size_t		i;
	size_t		count;

	if (!data)
		return (error_message("ERROR: data struct not init", NULL));
	i = 0;
	data->mapinfo->map_height = row_count(text->grid);
	count = data->mapinfo->map_height;
	data->mapinfo->grid = (char **)ft_calloc (count + 1, sizeof(char *));
	if (!data->mapinfo->grid)
		return (error_message("ERROR: calloc fail in map_init", NULL));
	while (i < count)
	{
		data->mapinfo->grid[i] = ft_strdup(text->grid[i]);
		if (!data->mapinfo->grid[i])
			return (error_message("ERROR: ft_strdup fail in map_init", NULL));
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
		return (error_message("ERROR: problems copying grid in init\n", NULL));
	(*data)->textinfo = text;
	(*data)->player = (t_player *)ft_calloc(1, sizeof(t_player));
	if (!(*data)->player)
		return (error_message("ERROR: problems init player\n", NULL));
	(*data)->ray = (t_ray *)ft_calloc(1, sizeof(t_ray));
	if (!(*data)->ray)
		return (error_message("ERROR: problems init ra\n", NULL));
	(*data)->mapinfo = (t_mapinfo *)ft_calloc(1, sizeof(t_mapinfo));
	if (!(*data)->mapinfo)
		return (error_message("ERROR: problems init map\n", NULL));
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
	if (ft_init_minimap(*data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

//function loads the sky and floor colours and creates a background image
//of the two colours.  We split it 50/50 for now. Function also checks
//the image was created and saves the address.
int	ft_init_background(t_data *data)
{
	data->background.img = mlx_new_image(data->mlx_conn, WIDTH, HEIGHT);
	if (!data->background.img)
		return (error_message("ERROR: problem initiating background\n", NULL));
	data->background.img_addr = (int *)mlx_get_data_addr(data->background.img, \
			&data->background.bpp, &data->background.line_len, \
			&data->background.endian);
	if (!data->background.img_addr)
		return (error_message("ERROR: problem getting background address\n", NULL));
	return (EXIT_SUCCESS);
}
