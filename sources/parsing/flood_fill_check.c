/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:44:09 by kbolon            #+#    #+#             */
/*   Updated: 2024/08/20 14:00:27 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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

/*void	error_check(t_mapinfo tmp, t_mapinfo *map)
{
	if (!(tmp.exit_x == 1 && tmp.points == 0))
	{
		free_memory(tmp.grid);
		free_game(game);
		error_message("Error\nNo valid path available");
	}
}*/

int	path_checker(t_mapinfo *game, int y, int x)
{
	if (y < 0 || y >= game->height || x < 0 || x >= game->width)
	{
		ft_printf("Map is not enclosed");
		return (1);
	}
	if (game->grid[y][x] == '1')
		return (0);
	game->grid[y][x] = '1';
	if (path_checker(game, y, x - 1) || path_checker(game, y, x + 1) \
		|| path_checker(game, y - 1, x) || path_checker(game, y + 1, x))
	{
		return (1);
	}
	return (0);
}

void	flood_fill(t_mapinfo *game)
{
	t_mapinfo		tmp;
	int				i;

	i = 0;
	tmp.width = game->width;
	tmp.height = game->height;
	tmp.player_x = game->player_x;
	tmp.player_y = game->player_y;
	tmp.grid = (char **) malloc (sizeof(char *) * (tmp.height + 1));
	if (!tmp.grid)
		error_message("Error\nmemory allocation fail in tmp.grid");
	while (i < tmp.height)
	{
		tmp.grid[i] = ft_strdup(game->grid[i]);
		i++;
	}
	tmp.grid[i] = NULL;
//	path_checker(&tmp, tmp.player_y, tmp.player_x);
    if (path_checker(&tmp, tmp.player_y, tmp.player_x)) {
        printf("Map is not enclosed.\n");
    } else {
        printf("Map is enclosed.\n");
    }
	free_memory(tmp.grid);
}

