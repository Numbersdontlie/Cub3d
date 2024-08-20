/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:47:58 by kbolon            #+#    #+#             */
/*   Updated: 2024/08/20 13:55:10 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	error_message(char *str)
{
	ft_putendl_fd(str, 2);
	exit (1);
}

void	error_message_simple(char *str, char **arr)
{
	if (arr)
		free_memory(arr);
	ft_putendl_fd(str, 2);
	exit (1);
}

void	ft_malloc_error(void)
{
	perror("Problem with memory allocation");
	exit(EXIT_FAILURE);
}

/*void	error_message_map(char *str, t_mapinfo *map)
{
	if (!map->file)
		free_game(file);

	//free images here too
	if (!map->img)
	{
		mlx_close_window(map->mlx);
		mlx_terminate(map->mlx);
		free(map->img);
	}
	error_message(str);
}*/
