/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:38:56 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/29 09:04:04 by kbolon           ###   ########.fr       */
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
	arr = NULL;
}

//Function to exit the program in a clean way
//it destroy the image, window and display before freeing memory
void	ft_clean_exit(t_data *data)
{
	free_textures(data);
	if (data->path)
		free_memory(data->path);
	if (data->mlx_window)
	{
		mlx_destroy_window(data->mlx_conn, data->mlx_window);
		data->mlx_window = NULL;
	}
	if (data->mapinfo)
		free_mapstruct(data);
	if (data->player)
		free(data->player);
	if (data->ray)
		free(data->ray);
	if (data->textinfo)
		free_text(data->textinfo);
	if (data->mlx_conn)
	{
		mlx_destroy_display(data->mlx_conn);
		free(data->mlx_conn);
		data->mlx_conn = NULL;
	}
	free(data);
	exit(EXIT_SUCCESS);
}

void	free_text(t_textinfo *text)
{
	if (text)
	{
		if (text->paths)
			free_memory(text->paths);
		if (text->ceiling_rgb)
			free(text->ceiling_rgb);
		if (text->floor_rgb)
			free(text->floor_rgb);
		if (text->grid)
			free_memory(text->grid);
		free(text);
	}
}

void	free_textures(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (data->textureinfo[i] && data->textureinfo[i]->img)
		{
			mlx_destroy_image(data->mlx_conn, data->textureinfo[i]->img);
			data->textureinfo[i]->img = NULL;
		}
		if (data->textureinfo[i])
		{
			free(data->textureinfo[i]);
			data->textureinfo[i] = NULL;
		}
	}
}

void	free_mapstruct(t_data *data)
{
	if (data->mapinfo->grid)
	{
		free_memory(data->mapinfo->grid);
		data->mapinfo->grid = NULL;
	}
	if (data->mapinfo)
	{
		free(data->mapinfo);
		data->mapinfo = NULL;
	}
}