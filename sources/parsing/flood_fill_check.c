/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:44:09 by kbolon            #+#    #+#             */
/*   Updated: 2024/10/11 13:00:44 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*function will return x and y value depending on input for values
given.  For instance, it will find which x and y value the player is 
initially located on grid so we can fill our player struct with*/
int	find_item(char **grid, char axis)
{
	int	x;
	int	y;
	int	height;
	int	length;

	y = 0;
	height = row_count(grid);
	length = ft_strlen(grid[0]);
	while (y < height)
	{
		x = 0;
		while (x < length)
		{
			if (ft_strchr("NSEW", grid[y][x]))
			{
				if (axis == 'x')
					return (x);
				else
					return (y);
			}
			x++;
		}
		y++;
	}
	return (0);
}

/*checks the path of the player using flood fill to see if the room is
enclosed and that they are not "stuck"*/
int	path_checker(char **game, size_t y, size_t x)
{
	size_t	line_count;

	line_count = row_count(game);		
	if (y >= line_count || !game[y] || x >= ft_strlen(game[y]) || !game[y][x] || \
		y < 0 || x < 0)
		return (1);
	if (game[y][x] == ' ')
	{
		if (game[y][x - 1] == '0' || game[y][x + 1] == '0' || \
		game[y - 1][x] == '0' || game[y + 1][x] == '0')
			return (1);
		return (0);
	}
	if (game[y][x] == '1' || game[y][x] == 'V')
		return (0);
	game[y][x] = 'V';
	if (path_checker(game, y, x - 1) || path_checker(game, y, x + 1) \
		|| path_checker(game, y - 1, x) || path_checker(game, y + 1, x))
	{
		return (1);
	}
	return (0);
}

/*uses flood fill to see if the room is enclosed*/
void	flood_fill(char **game)
{
	size_t	player_x;
	size_t	player_y;
	size_t	i;
	char	**arr;

	i = 0;
	player_x = find_item(game, 'x');
	player_y = find_item(game, 'y');
	check_map_size(game);
	arr = (char **) malloc (sizeof(char *) * (row_count(game) + 1));
	if (!arr)
		error_message("Error\nmemory allocation fail in tmp.grid");
	while (i < row_count(game))
	{
		arr[i] = ft_strdup(game[i]);
		i++;
	}
	arr[i] = NULL;
	if (path_checker(arr, player_y, player_x))
	{
		free_memory(arr);
		error_message("ERROR: Map is not enclosed\n");
	}
	else
		free_memory(arr);
}

void	check_map_size(char **grid)
{
	int	line_count;

	line_count = row_count(grid);
	if (line_count <= 2)
		error_message("ERROR: Map is too small\n");
}
