/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:38:56 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/05 16:50:44 by kbolon           ###   ########.fr       */
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

//Function to exit the program in a clean way
//it destroy the image, window and display before freeing memory
void	ft_clean_exit(t_data *data)
{
	if (data->mlx_conn)
	{
		mlx_destroy_image(data->mlx_conn, data->img.img);
		mlx_destroy_window(data->mlx_conn, data->mlx_window);
		mlx_destroy_display(data->mlx_conn);
		free(data->mlx_conn);
	}
	if (data->mapinfo)
	{
		if (data->mapinfo->path)
			free (data->mapinfo->path);
		if (data->mapinfo->grid)
			free_memory (data->mapinfo->grid);
		free(data->mapinfo);
	}
//	if (data->map)
//		free_memory(data->map);
//		free(data->map);
	if (data->textinfo)
		free_text(data->textinfo);
	if (data->player)
		free(data->player);
	free (data); 
}

void	free_text(t_textinfo *text)
{
	if (text)
	{
		if (text->north)
			free(text->north);
		if (text->south)
			free(text->south);
		if (text->east)
			free(text->east);
		if (text->west)
			free(text->west);
		if (text->ceiling_rgb)
			free_memory(text->ceiling_rgb);
		if (text->floor_rgb)
			free_memory(text->floor_rgb);
		if (text->grid)
			free_memory(text->grid);
		free (text);
	}
}

void	free_map(t_mapinfo *map)
{
	if (map)
	{
/*		if (map->fd)
			close(map->fd);
		if (map->path)
			free (map->path);
		if (map->grid)
			free_memory(map->grid);*/
		free (map);
	}
}
