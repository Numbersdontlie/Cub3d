/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:41:29 by kbolon            #+#    #+#             */
/*   Updated: 2024/08/26 13:50:23 by kbolon           ###   ########.fr       */
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

void check_args(char *arr)
{
	char		**grid;

	grid = read_map(arr);
	if (!grid)
		error_message("ERROR: problem reading map");
//	valid_chars(grid);
//	check_map_items(grid);
//	flood_fill(grid);
	free_memory(grid);
}

t_textinfo	*ft_initialize_textinfo(char **arr)
{
	char		**grid;
	t_textinfo	*text;
	
	grid = read_map(*arr);
	if (!grid)
		error_message("ERROR: problem reading map");
	text = (t_textinfo *) ft_calloc (1, sizeof(t_textinfo));
	if (!text)
		error_message_simple("ERROR: calloc fail in text_init", grid);
	text->north = find_cardinal_paths(grid, "NO");
	grid = update_grid(grid, text->north);
	text->south = find_cardinal_paths(grid, "SO");
	grid = update_grid(grid, text->south);

	text->east = find_cardinal_paths(grid, "EA");
	grid = update_grid(grid, text->east);
//	printf("e path: %s\n", text->east);
	text->west = find_cardinal_paths(grid, "WE");
	grid = update_grid(grid, text->west);
//	printf("w path: %s\n", text->west);
	text->floor = find_floor_ceiling(grid, 'F');
//	text->floor = find_cardinal_paths(grid, "F");
	grid = update_grid(grid, (char *)text->floor);
//	printf("floor path: %s\n", (char *)text->floor);
	text->ceiling = find_floor_ceiling(grid, 'C');
//	text->ceiling = find_cardinal_paths(grid, "C");
	grid = update_grid(grid, (char *)text->ceiling);
//	printf("c path: %s\n", (char *)text->ceiling);
	text->grid = remove_empty_lines(grid);
	return (text);
}

int	main(int ac, char **av)
{
//	t_mapinfo	*map;
	t_textinfo	*text;

	if (ac != 2)
		error_message("ERROR: include ./cub3D & .cub\n");
	check_extension(av[1]);
	check_args(av[1]);
	text = ft_initialize_textinfo(&av[1]);
	if (!text)
		error_message_text("ERROR: problem loading text");

//	printf("x: %zu\n", map->player_x);
	printf("EVERYTHING OK\n");
	
	return (0);
}

