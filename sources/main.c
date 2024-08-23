/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:41:29 by kbolon            #+#    #+#             */
/*   Updated: 2024/08/23 16:55:19 by kbolon           ###   ########.fr       */
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
	char		*NO_path;
	char		*SO_path;
	char		*WE_path;
	char		*EA_path;
	char		*F;
	char		*C;

	grid = read_map(arr);
	NO_path = find_cardinal_paths(grid, "NO");
	grid = update_grid(grid, NO_path);
	free(NO_path);
	SO_path = find_cardinal_paths(grid, "SO");
	grid = update_grid(grid, SO_path);
	free(SO_path);
	EA_path = find_cardinal_paths(grid, "EA");
	grid = update_grid(grid, EA_path);
	free(EA_path);
	WE_path = find_cardinal_paths(grid, "WE");
	grid = update_grid(grid, WE_path);
	free(WE_path);
	F = find_floor_ceiling(grid, 'F');
	grid = update_grid(grid, F);
	free(F);
	C = find_floor_ceiling(grid, 'C');
	grid = update_grid(grid, C);
	free(C);
	grid = remove_empty_lines(grid);
	valid_chars(grid);
	check_map_items(grid);
	flood_fill(grid);
	free_memory(grid);
	printf("EVERYTHING OK\n");
}

int	main(int ac, char **av)
{
	if (ac != 2)
		error_message("ERROR: include ./cub3D & .cub\n");
	check_extension(av[1]);
	check_args(av[1]);
	return (0);
}

