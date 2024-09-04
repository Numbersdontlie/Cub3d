/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:41:29 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/04 16:53:36 by kbolon           ###   ########.fr       */
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
//	t_data		*data;

	if (ac != 2)
		error_message("ERROR: include ./cub3D & .cub\n");
	check_extension(av[1]);
//	data = (t_data *)ft_calloc(1, sizeof(t_data));
	text = ft_initialize_textinfo(&av[1]);
	if (!text)
		error_message_text("ERROR: problem loading text", text);
	check_args(text);
//	ft_initialize_data(data);
	printf("EVERYTHING WORKS\n");
	free_text(text);
//	ft_clean_exit(data);
	return (0);
}

