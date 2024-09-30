/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:52:09 by luifer            #+#    #+#             */
/*   Updated: 2024/09/30 14:34:40 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//Function to create a connection with the library and creates a window
//into that connection. It also checks that connection and window
//were created without problems
int	ft_initialize_connection(t_data *data)
{
	data->mlx_conn = mlx_init();
	if (!data->mlx_conn)
	{
		ft_putstr_fd("ERROR: problems with mlx_init\n", 2);
		return (EXIT_FAILURE);
	}
	data->mlx_window = mlx_new_window(data->mlx_conn, WIDTH, HEIGHT, "Cub3D");
	if (!data->mlx_window)
	{
		mlx_destroy_display(data->mlx_conn);
		free(data->mlx_conn);
		ft_putstr_fd("ERROR: problems with mlx window\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

//Function to initialize the image, it creates the new image using 
//the mlx library and checks it was correctly created and saves the image address
int	ft_initialize_textures(t_data *data)
{
	int		i;

	i = 0;
	while (data->textinfo->paths[i])
	{
		data->textureinfo[i] = (t_img *)ft_calloc(1, sizeof(t_img));
		if (!data->textureinfo[i])
			return (ft_clear_textures(data, i));
		data->textureinfo[i]->img = mlx_xpm_file_to_image(data->mlx_conn, data->textinfo->paths[i], \
			&data->textureinfo[i]->texture_width, &data->textureinfo[i]->texture_height);
		if (!data->textureinfo[i]->img)
			return (ft_clear_textures(data, i));
		data->textureinfo[i]->img_addr = (int *)mlx_get_data_addr(data->textureinfo[i]->img, \
			&data->textureinfo[i]->bpp, &data->textureinfo[i]->line_len, \
			&data->textureinfo[i]->endian);
		if (!data->textureinfo[i]->img_addr)
			return (ft_clear_textures(data, i));
		i++;
	}
	return (EXIT_SUCCESS);
}

//function destroys the texture images if any problems were found
//during the loading of each texture.
int	ft_clear_textures(t_data *data, int i)
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
	ft_putstr_fd("ERROR: problems loading texture.\n", 2);
	return (EXIT_FAILURE);
}

