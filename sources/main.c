/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:41:29 by kbolon            #+#    #+#             */
/*   Updated: 2024/10/08 12:33:10 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void check_args(t_textinfo *text)
{
	valid_chars(text);
	check_map_items(text);
	flood_fill(text->grid);
}

//Function to parse the args 
//the idea is to call all the parsing function inside this one
int	ft_parse_args(t_data *data, char **av)
{
	if (check_extension(av[1]) == EXIT_FAILURE)
		ft_clean_exit(data);
	ft_parse_data(av[1], data);
}

int	main(int ac, char **av)
{
	t_data		*data;
	//t_textinfo	*text;//comenting this out. Will try to load the textures from the parsing

	if (ac != 2)
		error_message("ERROR: include ./cub3D & .cub\n");
	//data = NULL;
	ft_data_init(&data);
	
	check_extension(av[1]);
	text = ft_initialize_textinfo(&av[1]);
	if (!text)
		error_message("ERROR: problem loading text");
	check_args(text);
	if (ft_initialize_data(&data, text) == EXIT_FAILURE)
		error_exit("ERROR: problem loading text", data, NULL);
	ft_init_game(data);
	mlx_loop_hook(data->mlx_conn, ft_render, data);
	mlx_hook(data->mlx_window, KeyPress, KeyPressMask, ft_handle_key, data);
	mlx_hook(data->mlx_window, KeyRelease, KeyReleaseMask, ft_release_key, data);
	mlx_loop(data->mlx_conn);
	ft_exit_game(data);
//	free_text(text);
//	free(data);
	return (EXIT_SUCCESS);
}
