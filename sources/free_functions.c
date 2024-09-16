/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:38:56 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/16 17:12:19 by kbolon           ###   ########.fr       */
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
	if (data->imginfo)
	{
		mlx_destroy_image(data->mlx_conn, data->imginfo->img);
		free(data->imginfo);
	}
	if (data->mlx_window)
		mlx_destroy_window(data->mlx_conn, data->mlx_window);
	if (data->texture_pixels)
		free_pixels(data);
	if (data->mapinfo)
	{
		if (data->mapinfo->path)
			free (data->mapinfo->path);
		if (data->mapinfo->grid)
			free_memory (data->mapinfo->grid);
		free(data->mapinfo);
	}
	if (data->player)
		free(data->player);
	if (data->mlx_conn)
	{
		mlx_destroy_display(data->mlx_conn);
		free(data->mlx_conn);
	}
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
//		free (text);
	}
}

/*void	free_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->textures[i])
		{
			if(data->textures[i]->img)
			{
				mlx_destroy_image(data->mlx_conn, data->textures[i]->img);
				data->textures[i]->img = NULL;
			}
			free(data->textures[i]);
		}
		i++;
	}
	free(data->textures);
	data->textures = NULL;
}*/

void	free_pixels(t_data *data)
{
	int	i;

	i = 0;
	if (data->texture_pixels)
	{
		while (i < 4)
		{
			if (data->texture_pixels[i])
				free(data->texture_pixels[i]);
			i++;
		}
		free(data->texture_pixels);
	}
}

