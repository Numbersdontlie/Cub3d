/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:38:56 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/27 14:00:04 by kbolon           ###   ########.fr       */
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
	if (data->img_FC)
		free_img_FC(data);
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
		if (data->imginfo[i] && data->imginfo[i]->img)
		{
			mlx_destroy_image(data->mlx_conn, data->imginfo[i]->img);
			data->imginfo[i]->img = NULL;
		}
		if (data->imginfo[i])
		{
			free(data->imginfo[i]);
			data->imginfo[i] = NULL;
		}
	}
}

void	free_img_FC(t_data *data)
{
	if (data->img_FC)
	{
		if (data->img_FC->img)
		{
			mlx_destroy_image(data->mlx_conn, data->img_FC->img);
			data->img_FC->img = NULL;
		}
		if (data->img_FC)
		{
			free(data->img_FC);
			data->img_FC = NULL;
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