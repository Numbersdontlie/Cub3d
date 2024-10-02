/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:41:29 by kbolon            #+#    #+#             */
/*   Updated: 2024/10/02 16:55:37 by kbolon           ###   ########.fr       */
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
		error_message("ERROR: include ./cub3D & .cub\n", NULL);
	data = NULL;
	check_extension(av[1]);
	text = ft_initialize_textinfo(&av[1]);
	if (!text)
		error_message("ERROR: problem loading text", NULL);
	check_args(text);
	if (ft_initialize_data(&data, text) == EXIT_FAILURE)
		error_exit("ERROR: problem loading text", data, text);
//	render_map(data); mini map
	if (ft_launch_game(data) == EXIT_FAILURE)
		error_exit("ERROR: problem loading text", data, text);
	ft_make_raycasting(data->player, data);	
	mlx_hook(data->mlx_window, KeyPress, KeyPressMask, ft_handle_key, data);
	mlx_hook(data->mlx_window, KeyRelease, KeyReleaseMask, ft_release_key, data);
	mlx_loop_hook(data->mlx_conn, ft_render, data);
	mlx_loop(data->mlx_conn);
	ft_exit_game(data);
	free_text(text);
	free(data);
	return (EXIT_SUCCESS);
}
