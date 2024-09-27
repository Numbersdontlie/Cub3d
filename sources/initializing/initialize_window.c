/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:52:09 by luifer            #+#    #+#             */
/*   Updated: 2024/09/27 14:08:41 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//Function to initialize the image, it will initialize an empty image structure
//create the new image using the mlx library and check that was correctly created
//assign the image address
int	ft_initialize_imginfo(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!data->imginfo[i])
		{
			data->imginfo[i] = (t_img *)ft_calloc(1, sizeof(t_img));
			if (!data->imginfo[i])
				error_exit("ERROR: Memory allocation failed for imginfo[i]\n", data, NULL);
		}
		if (data->imginfo[i]->img)
			mlx_destroy_image(data->mlx_conn, data->imginfo[i]->img);
		data->imginfo[i]->img = mlx_new_image(data->mlx_conn, WIDTH, HEIGHT);
		if (!data->imginfo[i]->img)
			error_exit("ERROR: failed to create image\n", data, NULL);
		data->imginfo[i]->img_addr = mlx_get_data_addr(data->imginfo[i]->img, \
			&data->imginfo[i]->bpp, &data->imginfo[i]->line_len, \
			&data->imginfo[i]->endian);
		if (!data->imginfo[i]->img_addr)
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

//Function to initialize the textures (NORTH, SOUTH, WEST, EAST)
//it allocate memory for the textures and call the put img into buffer function
//to load the textures in the data structure
int	ft_initialize_textures(t_data *data)
{
	char	*t_path[4];
	int		i;

	t_path[0] = data->textinfo->north;
	t_path[1] = data->textinfo->east;
	t_path[2] = data->textinfo->south;
	t_path[3] = data->textinfo->west;
	i = 0;

	while (i < 4)
	{
		//width and height might be window size and not image size???
		data->imginfo[i]->img = mlx_xpm_file_to_image(data->mlx_conn, t_path[i], \
		&data->imginfo[i]->texture_width, &data->imginfo[i]->texture_height);
		if (!data->imginfo[i]->img)
		{
			ft_destroy_texture(data, i);
			error_exit("ERROR: Failed to load texture img\n", data, NULL);
		}
		data->imginfo[i]->img_addr = mlx_get_data_addr(data->imginfo[i]->img, \
			&data->imginfo[i]->bpp, &data->imginfo[i]->line_len, &data->imginfo[i]->endian);
		if (!data->imginfo[i]->img_addr)
		{
			ft_destroy_texture(data, i);
			error_exit("ERROR: failure to get img address\n", data, NULL);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	ft_destroy_texture(t_data *data, int wall)
{
	int	i;

	i = -1;
	while (++i < wall)
	{
		if (data->imginfo[i]->img)
		{
			mlx_destroy_image(data->mlx_conn, data->imginfo[i]->img);
			data->imginfo[i]->img = NULL;
		}
	}
}

