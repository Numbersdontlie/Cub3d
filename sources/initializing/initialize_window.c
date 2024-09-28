/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:52:09 by luifer            #+#    #+#             */
/*   Updated: 2024/09/28 10:58:42 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//Function to initialize the image, it will initialize an empty image structure
//create the new image using the mlx library and check that was correctly created
//assign the image address
int	ft_initialize_textures(t_data *data)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		data->textureimginfo[i]->img = mlx_xpm_file_to_image(data->mlx_conn, data->path[i], \
			&data->textureimginfo[i]->texture_width, &data->textureimginfo[i]->texture_height);
		if (!data->textureimginfo[i]->img)
			error_exit("ERROR: failed to load texture\n", data, NULL);
		data->textureimginfo[i]->img_addr = (int *)mlx_get_data_addr(data->textureimginfo[i]->img, \
			&data->textureimginfo[i]->bpp, &data->textureimginfo[i]->line_len, \
			&data->textureimginfo[i]->endian);
		if (!data->textureimginfo[i]->img_addr)
			error_exit("ERROR: failed to get img address\n", data, NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}


//Function to initialize the connection with the minilibx library
//it creates a connection with the library and creates a window
//into that connection. It also check that connection and window
//where created without problem
int	ft_initialize_connection(t_data *data)
{
	data->mlx_conn = mlx_init();
	if (!data->mlx_conn)
		error_exit("ERROR: problems with mlx_init\n", data, NULL);
	data->mlx_window = mlx_new_window(data->mlx_conn, WIDTH, HEIGHT, "Cub3D");
	if (!data->mlx_window)
		error_exit("ERROR: problems with mlx window\n", data, NULL);
	return (EXIT_SUCCESS);
}


