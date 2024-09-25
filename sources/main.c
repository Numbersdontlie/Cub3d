/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:41:29 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/25 16:13:34 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void check_args(t_textinfo *text)
{
	valid_chars(text);
	check_map_items(text);
	flood_fill(text->grid);
}


int	main(int ac, char **av)
{
	t_textinfo	*text;
	t_data		*data;

	if (ac != 2)
		error_message("ERROR: include ./cub3D & .cub\n");
	data = NULL;
	check_extension(av[1]);
	text = ft_initialize_textinfo(&av[1]);
	if (!text)
		error_message("ERROR: problem loading text");
	check_args(text);
	if (ft_initialize_data(&data, text) == EXIT_FAILURE)
		error_message_data("ERROR: problem loading text", data, NULL);
	if (ft_initialize_connection(data) == EXIT_FAILURE)
		error_message_data("ERROR: problem initiating connection\n", data, NULL);
	if (ft_initialize_imginfo(data) == EXIT_FAILURE)
		error_message_data("ERROR: problem initiating imginfo\n", data, NULL);
	if (ft_initialize_textures(data) == EXIT_FAILURE)
	{
		mlx_destroy_image(data->mlx_conn, data->imginfo->img);
		free(data->imginfo);
		mlx_destroy_window(data->mlx_conn, data->mlx_window);
		error_message_data("ERROR: problem initiating textures\n", data, NULL);
	}
	ft_game(data);
//	render_map(data); mini map
	ft_initialize_events(data);
	ft_clean_exit(data);
	free_text(text);
	free(data);
	return (EXIT_SUCCESS);
}
