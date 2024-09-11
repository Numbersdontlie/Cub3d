/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:41:29 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/11 19:55:34 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void check_args(t_textinfo *text)
{
	valid_chars(text);
	check_map_items(text);
	check_rgb_for_illegal_chars(text, text->floor_rgb);
	check_rgb_for_illegal_chars(text, text->ceiling_rgb);
	flood_fill(text->grid);
}

int	main(int ac, char **av)
{
//	t_mapinfo	*map;
	t_textinfo	*text;
	t_data		*data;

	if (ac != 2)
		error_message("ERROR: include ./cub3D & .cub\n");
	check_extension(av[1]);
	text = ft_initialize_textinfo(&av[1]);
	if (!text)
		error_message("ERROR: problem loading text");
	check_args(text);
	data = ft_initialize_data(text);
	if (!data)
		error_message_text("ERROR: problem loading text", text);
//	map = ft_initialize_map(data, text);
//	if (!map)
//		error_message_data("ERROR: problems copying grid in init\n", data, text);
	if (ft_initialize_connection(data) == EXIT_FAILURE)
		error_message_data("ERROR: problem initiating connection\n", data, text);
	if (ft_initialize_textures(data) == EXIT_FAILURE)
		error_message_data("ERROR: problem initiating textures\n", data, text);
//	free(data->img)
	free_text(text);
	ft_clean_exit(data);
//	free_map(map);
	return (0);
}

/*
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop(game->mlx);
	free(game->img);
	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	free_game(game);*/

