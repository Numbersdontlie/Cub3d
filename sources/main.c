/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:41:29 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/19 17:52:16 by kbolon           ###   ########.fr       */
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
	check_extension(av[1]);
	text = ft_initialize_textinfo(&av[1]);
	if (!text)
		error_message("ERROR: problem loading text");
	check_args(text);
	data = ft_initialize_data(text);
	if (!data)
		error_message_text("ERROR: problem loading text", text);
	if (ft_initialize_connection(data) == EXIT_FAILURE)
		error_message_data("ERROR: problem initiating connection\n", data, text);
//	if (ft_initialize_imginfo(data) == EXIT_FAILURE)
//		error_message_data("ERROR: problem initiating imginfo\n", data, NULL);
	if (ft_initialize_textures(data) == EXIT_FAILURE)
	{
		error_message_data("ERROR: problem initiating textures\n", data, text);
		mlx_destroy_display(data->mlx_conn);
		free(data->mlx_conn);
	}
	ft_initialize_events(data);
	if (data->mlx_conn)
	{
		mlx_destroy_display(data->mlx_conn);
		free(data->mlx_conn);
	}
	ft_clean_exit(data);
	free_text(text);
	free(text);
	free(data);
	return (EXIT_SUCCESS);
}
