/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:41:29 by kbolon            #+#    #+#             */
/*   Updated: 2024/08/28 15:31:12 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	print_map(char **arr)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = row_count(arr);
	while (i < count)
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

void check_args(t_textinfo *text)
{
	valid_chars(text->grid);
	check_map_items(text->grid);
	flood_fill(text->grid);
}

int	main(int ac, char **av)
{
//	t_mapinfo	*map;
	t_textinfo	*text;

	if (ac != 2)
		error_message("ERROR: include ./cub3D & .cub\n");
	check_extension(av[1]);
	text = ft_initialize_textinfo(&av[1]);
	if (!text)
		error_message_text("ERROR: problem loading text", text);
	check_args(text);
//	printf("ceiling red: %s\n", text->ceiling_rgb[0]);
	printf("EVERYTHING OK\n");
	free_text(text);
	return (0);
}

