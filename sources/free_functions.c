/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:38:56 by kbolon            #+#    #+#             */
/*   Updated: 2024/08/19 13:46:25 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_memory(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/*void	free_game(t_game *game)
{
	if (game)
	{
		free_memory(game->grid);
		free(game);
	}
}*/

/*void	error_message_game(char *str, t_game *game)
{
	if (!game->grid)
		free_game(game);
	if (!game->img)
	{
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
		free(game->img);
	}
	error_message(str);
}*/