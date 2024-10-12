/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:38:56 by kbolon            #+#    #+#             */
/*   Updated: 2024/10/12 10:20:18 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_memory(char **arr)
{
	int	i;

	i = 0;
	if (arr[i])
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
	}
	free(arr);
	arr = NULL;
}

void	ft_exit_game(t_data *data)
{
	if (data->mlx_window)
		mlx_destroy_window(data->mlx_conn, data->mlx_window);
	if (data->mlx_conn)
	{
		mlx_destroy_display(data->mlx_conn);
		mlx_loop_end(data->mlx_conn);
		free(data->mlx_conn);
	}
	ft_clean_exit(data);
}

//Function to exit the program in a clean way
//it destroy the image, window and display before freeing memory

//add new free for new image
void	ft_clean_exit(t_data *data)
{
	if (data->path)
		free_memory(data->path);
	if (data->mapinfo)
		free_mapstruct(data);
	if (data->textinfo)
		free_text(data->textinfo);
	if (data->textures)
		free_textures(data->textures);
	if (data->texture_pixels)
		free_textures(data->texture_pixels);	
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

void	free_textures(int **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
}
