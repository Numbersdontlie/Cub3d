/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:47:58 by kbolon            #+#    #+#             */
/*   Updated: 2024/08/27 10:29:39 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	error_message(char *str)
{
	perror(str);
	exit (1);
}

void	error_message_simple(char *str, char **arr)
{
	if (arr)
		free_memory(arr);
	perror(str);
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

void	error_message_text(char *str, t_textinfo *text)
{
	free_text(text);
	perror(str);
	exit (1);
}
