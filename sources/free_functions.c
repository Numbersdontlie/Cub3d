/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:38:56 by kbolon            #+#    #+#             */
/*   Updated: 2024/08/28 14:44:53 by lperez-h         ###   ########.fr       */
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
int	ft_clean_exit(t_data *data)
{
	mlx_destroy_image(data->mlx_conn, data->img.img);
	mlx_destroy_window(data->mlx_conn, data->mlx_window);
	mlx_destroy_display(data->mlx_conn);
	free(data->mlx_conn);
	exit(EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

void	free_and_make_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_text(t_textinfo *text)
{
	if (text)
	{
		free_and_make_null((void **)&text->north);
		free_and_make_null((void **)&text->south);
		free_and_make_null((void **)&text->east);
		free_and_make_null((void **)&text->west);
		free_and_make_null((void **)&text->floor);
		free_and_make_null((void **)&text->ceiling);
	}
	if (text->grid)
	{
		free_memory(text->grid);
		text->grid = NULL;
	}
	free_and_make_null((void **)&text);
}
