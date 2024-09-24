/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:05:26 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/24 16:00:29 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

void	make_tiles(t_data *data, int x, int y, int colour)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;

	i = 0;
	start_x = x * MINI;
	start_y = y * MINI;
	while (i < MINI)
	{
		j = 0;
		while (j < MINI)
		{
			mlx_pixel_put(data->mlx_conn, data->mlx_window, start_x + i, start_y + j, colour);
			j++;
		}
		i++;
	}
}

void	render_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->mapinfo->grid[i])
	{
		j = 0;
		while (data->mapinfo->grid[i][j])
		{
			if (data->mapinfo->grid[i][j] == 1)
				make_tiles(data, j, i, WHITE);
			else if (data->mapinfo->grid[i][j] == 'N' || data->mapinfo->grid[i][j] == 'E' ||\
				data->mapinfo->grid[i][j] == 'S' || data->mapinfo->grid[i][j] == 'W')
				make_tiles(data, j, i, RED);
			else
				make_tiles(data, j, i, BLACK);
			j++;
		}
		i++;
	}
}
