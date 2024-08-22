/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:41:29 by kbolon            #+#    #+#             */
/*   Updated: 2024/08/22 12:53:45 by kbolon           ###   ########.fr       */
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
//	valid_chars(grid);
//	check_map_items(grid);
//	flood_fill(grid);
//	printf("grid checked\n");
	NO_path = find_cardinal_paths(grid, "NO");
	SO_path = find_cardinal_paths(grid, "SO");
	EA_path = find_cardinal_paths(grid, "EA");
	WE_path = find_cardinal_paths(grid, "WE");
	F = find_floor_ceiling(grid, 'F');
	C = find_floor_ceiling(grid, 'C');
	printf("WE: %s\n", WE_path);
	free_memory(grid);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		error_message("ERROR: include ./cub3D & .cub\n");
	check_extension(av[1]);
	check_args(av[1]);
	return (0);
}

