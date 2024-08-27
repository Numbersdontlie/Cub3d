/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:41:29 by kbolon            #+#    #+#             */
/*   Updated: 2024/08/27 12:30:49 by kbolon           ###   ########.fr       */
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

char	**update_text_info(char **path, char **grid, char *s)
{
	char		**temp_grid;

//	if (ft_strchr(**path, 'F' || ft_strchr(**path, 'C')))
	*path = find_cardinal_paths(grid, s);
	temp_grid = update_grid(grid, *path);
//	free_memory(grid);
	return (temp_grid);
}


t_textinfo	*ft_initialize_textinfo(char **arr)
{
	char		**grid;
//	char		**temp_grid;
	t_textinfo	*text;

	grid = read_map(*arr);
	if (!grid)
		error_message("ERROR: problem reading map");
	text = (t_textinfo *) ft_calloc (1, sizeof(t_textinfo));
	if (!text)
	{
		free_memory(grid);
		error_message_simple("ERROR: calloc fail in text_init", grid);
	}
	grid = update_text_info(&text->north, grid, "NO");
	grid = update_text_info(&text->south, grid, "SO");
	grid = update_text_info(&text->west, grid, "WE");
	grid = update_text_info(&text->east, grid, "EA");

/*	text->floor = find_floor_ceiling(grid, 'F');
	grid = update_grid(grid, (char *)text->floor);
	text->ceiling = find_floor_ceiling(grid, 'C');
	grid = update_grid(grid, text->ceiling);*/
	text->grid = remove_empty_lines(grid);
	free_memory(grid);
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
		error_message_text("ERROR: problem loading text", text);

//	printf("x: %zu\n", map->player_x);
	printf("EVERYTHING OK\n");
	free_text(text);
	return (0);
}

