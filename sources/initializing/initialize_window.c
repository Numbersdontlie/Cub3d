/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:52:09 by luifer            #+#    #+#             */
/*   Updated: 2024/09/29 10:44:05 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//Function to initialize the connection with the minilibx library
//it creates a connection with the library and creates a window
//into that connection. It also check that connection and window
//where created without problem
int	ft_initialize_connection(t_data *data, t_textinfo *text)
{
	data->mlx_conn = mlx_init();
	if (!data->mlx_conn)
		error_exit("ERROR: problems with mlx_init\n", data, text);
	data->mlx_window = mlx_new_window(data->mlx_conn, WIDTH, HEIGHT, "Cub3D");
	if (!data->mlx_window)
	{
		mlx_destroy_display(data->mlx_conn);
		free(data->mlx_conn);
		error_exit("ERROR: problems with mlx window\n", data, text);
	}
	return (EXIT_SUCCESS);
}

//Function to initialize the image, it will initialize an empty image structure
//create the new image using the mlx library and check that was correctly created
//assign the image address
int	ft_initialize_textures(t_data *data, t_textinfo *text)
{
	int		i;

	i = 0;
	while (data->textinfo->paths[i])
	{
		data->textureinfo[i] = (t_img *)ft_calloc(1, sizeof(t_img));
		if (!data->textureinfo[i])
			return (ft_clear_textures(data, i, text));
		data->textureinfo[i]->img = mlx_xpm_file_to_image(data->mlx_conn, data->textinfo->paths[i], \
			&data->textureinfo[i]->texture_width, &data->textureinfo[i]->texture_height);
		if (!data->textureinfo[i]->img)
			return (ft_clear_textures(data, i, text));
		data->textureinfo[i]->img_addr = (int *)mlx_get_data_addr(data->textureinfo[i]->img, \
			&data->textureinfo[i]->bpp, &data->textureinfo[i]->line_len, \
			&data->textureinfo[i]->endian);
		if (!data->textureinfo[i]->img_addr)
			return (ft_clear_textures(data, i, text));
		i++;
	}
	free_memory(data->textinfo->paths);//do we need to free it here?
	return (EXIT_SUCCESS);
}

int	ft_clear_textures(t_data *data, int i, t_textinfo *text)
{
	while (--i >= 0)
	{
		if (data->textureinfo[i])
		{
			if (data->textureinfo[i]->img)
				mlx_destroy_image(data->mlx_conn, data->textureinfo[i]->img);
			free(data->textureinfo[i]);
		}
	}
	free(data->textinfo->paths[i]);
	error_exit("ERROR: problems loading texture.\n", data, text);
	return (EXIT_FAILURE);
}

