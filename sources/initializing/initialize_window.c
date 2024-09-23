/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:52:09 by luifer            #+#    #+#             */
/*   Updated: 2024/09/23 14:21:55 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//Function to initialize the image, it will initialize an empty image structure
//create the new image using the mlx library and check that was correctly created
//assign the image address
int	ft_initialize_imginfo(t_data *data)
{
	if (data->imginfo && data->imginfo->img)
		mlx_destroy_image(data->mlx_conn, data->imginfo);
	data->imginfo = (t_img *)ft_calloc(1, sizeof(t_img));
	if (!data->imginfo)
		error_message("ERROR: failed to initiate img\n");
	data->imginfo->img = mlx_new_image(data->mlx_conn, WIDTH, HEIGHT);
	if (!data->imginfo->img)
		error_message("ERROR: failed to create image\n");
	data->imginfo->img_addr = (int *)mlx_get_data_addr(data->imginfo->img, \
		&data->imginfo->bpp, &data->imginfo->line_len, &data->imginfo->endian);
	if (!data->imginfo->img_addr)
		error_message("ERROR: failed to get img address\n");
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
		error_message("ERROR: problems with mlx_init\n");
	data->mlx_window = mlx_new_window(data->mlx_conn, WIDTH, HEIGHT, "Cub3D");
	if (!data->mlx_window)
		error_message("ERROR: problems with mlx window\n");
	return (EXIT_SUCCESS);
}

//Function to initialize the textures into the image structure
//it will load the xmp file into an image and get the data address
/*int	ft_initialize_texture_image(t_data *data, t_img **image, char *path)
{
	if (!path)
		error_message("ERROR: path missing\n");
	check_path(path);
	(*image)->img = mlx_xpm_file_to_image(data->mlx_conn, path, \
		&data->image_width, &data->image_height);
	if (!(*image)->img)
		error_message("ERROR: failed to load texture image\n");
	(*image)->img_addr = (int *)mlx_get_data_addr\
		((*image)->img, &(*image)->bpp, &(*image)->line_len, &(*image)->endian);
	if (!(*image)->img_addr)
		error_message("ERROR: failed to get image address\n");
	return (EXIT_SUCCESS);
}*/

//Function to initialize the textures (NORTH, SOUTH, WEST, EAST)
//it allocate memory for the textures and call the put img into buffer function
//to load the textures in the data structure
int	ft_initialize_textures(t_data *data)
{
	data->textures[N] = mlx_xpm_file_to_image(data->mlx_conn, \
		data->textinfo->north, &data->image_width, &data->image_height);
	if (!data->textures[N])
		error_message("ERROR: problems loading N texture\n");
	data->textures[E] = mlx_xpm_file_to_image(data->mlx_conn, \
		data->textinfo->east, &data->image_width, &data->image_height);
	if (!data->textures[E])
	{
		mlx_destroy_image(data->mlx_conn, data->textures[N]);
		error_message("ERROR: problems loading E texture\n");
	}
	data->textures[S] = mlx_xpm_file_to_image(data->mlx_conn, \
		data->textinfo->south, &data->image_width, &data->image_height);
	if (!data->textures[S])
	{
		mlx_destroy_image(data->mlx_conn, data->textures[N]);
		mlx_destroy_image(data->mlx_conn, data->textures[E]);
		error_message("ERROR: problems loading S texture\n");
	}
	data->textures[W] = mlx_xpm_file_to_image(data->mlx_conn, \
		data->textinfo->west, &data->image_width, &data->image_height);
	if (!data->textures[W])
	{
		mlx_destroy_image(data->mlx_conn, data->textures[N]);
		mlx_destroy_image(data->mlx_conn, data->textures[E]);
		mlx_destroy_image(data->mlx_conn, data->textures[S]);
		error_message("ERROR: problems loading W texture\n");
	}
	return (EXIT_SUCCESS);
}
