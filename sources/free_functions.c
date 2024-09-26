/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:38:56 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/26 13:15:40 by kbolon           ###   ########.fr       */
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
/*	if (data->textures)
	{
		ft_destroy_texture(data, 4);
		free(data->textures);
		data->textures = NULL;
	}*/
	if (data->imginfo)
	{
		if (data->imginfo->img)
		{
			mlx_destroy_image(data->mlx_conn, data->imginfo->img);
			data->imginfo->img = NULL;
		}
		free(data->imginfo);
		data->imginfo = NULL;
	}
	if (data->mlx_window)
	{
		mlx_destroy_window(data->mlx_conn, data->mlx_window);
		data->mlx_window = NULL;
	}
	if (data->mapinfo)
	{
		if (data->mapinfo->grid)
		{
			free_memory(data->mapinfo->grid);
			data->mapinfo->grid = NULL;
		}
		free(data->mapinfo);
		data->mapinfo = NULL;
	}
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
	exit(0);
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
		if (data->texture.textures[i])
		{
			mlx_destroy_image(data->mlx_conn, data->texture.textures[i]);
			data->texture.textures[i] = NULL;
		}
	}
}


