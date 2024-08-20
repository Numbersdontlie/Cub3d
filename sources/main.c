/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:41:29 by kbolon            #+#    #+#             */
/*   Updated: 2024/08/20 13:54:41 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	print_map(char **arr)
{
	int	count;
	int	i;

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
	t_mapinfo	*map;

	grid = read_map(arr);

//	print_map(map);
//	check_border(arr);
	valid_chars(grid);
	check_map_items(grid);
	map = ft_initialize_map(grid);
	if (!map)
	{
		free_memory(grid);
//		error_message_game("ERROR\n, issues making map", map);//need to free images or game??
		error_message("ERROR\n, issues making map");
	}
	flood_fill(map);
	printf("grid checked\n");
}

int	main(int ac, char **av)
{
	if (ac != 2)
		error_message("ERROR: include ./cub3D & .cub\n");
	check_extension(av[1]);
	check_args(av[1]);
	return (0);
}

