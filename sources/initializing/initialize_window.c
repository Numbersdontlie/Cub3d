/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:52:09 by luifer            #+#    #+#             */
/*   Updated: 2024/09/16 16:34:54 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//Function to initialize the image, it will initialize an empty image structure
//create the new image using the mlx library and check that was correctly created
//assign the image address
/*int	ft_initialize_image(t_data *data, t_img **image, int width, int height)
{
	*image = (t_img *)ft_calloc(1, sizeof(t_img));
	if (!(*image))
		return (EXIT_FAILURE);
	(*image)->img = mlx_new_image(data->mlx_conn, width, height);
	if (!(*image)->img)
		return (EXIT_FAILURE);
	(*image)->img_addr = (int *)mlx_get_data_addr
		((*image)->img, &(*image)->bpp, &(*image)->line_len, &(*image)->endian);
	if (!(*image)->img_addr)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}*/


//Function to initialize the connection with the minilibx library
//it creates a connection with the library and creates a window
//into that connection. It also check that connection and window
//where created without problem
int	ft_initialize_connection(t_data *data)
{
	data->mlx_conn = mlx_init();
	if (!data->mlx_conn)
		error_message("ERROR: problems with mlx_init\n");
	data->mlx_window = mlx_new_window(data->mlx_conn, data->window_height, \
		data->window_width, "Cub3D");
	if (!data->mlx_window)
		error_message("ERROR: problems with mlx window\n");
	return (EXIT_SUCCESS);
}

//Function to initialize the textures into the image structure
//it will load the xmp file into an image and get the data address
int	ft_initialize_texture_image(t_data *data, t_img **image, char *path)
{
	if (!(*image))
	{
		*image = (t_img *)ft_calloc(1, sizeof(t_img));
		if (!(*image))
			error_message("ERROR: failed to calloc t_img\n");
	}
	if (!path)
		error_message("ERROR: path missing\n");
	printf("Loading texture from path: %s\n", path);//
	(*image)->img = mlx_xpm_file_to_image(data->mlx_conn, path, \
		&data->image_width, &data->image_height);
	if (!(*image)->img)
		error_message("ERROR: failed to load texture image\n");
	(*image)->img_addr = (int *)mlx_get_data_addr\
		((*image)->img, &(*image)->bpp, &(*image)->line_len, &(*image)->endian);
	if (!(*image)->img_addr)
		error_message("ERROR: failed to get image address\n");
	return (EXIT_SUCCESS);
}

//Function to put the converted xpm image into an integer buffer
//use this function if we need to manipulate the image at all
//otherwise, use the mlx_xpm_file_to_image function as it is more
//efficient
int	*ft_put_img_into_buffer(t_data *data, char *path)
{
	t_img	*tmp;
	int		*buf;
	int		x;
	int		y;

	tmp = (t_img *)ft_calloc(1, sizeof(t_img));
	if (!(tmp))
		error_message("ERROR: problem callocing img\n");
	if (ft_initialize_texture_image(data, &tmp, path) == EXIT_FAILURE)
		error_message("ERROR: problems initializing textures");
	buf = ft_calloc(data->textinfo->size * data->textinfo->size, sizeof(int));
	if (!buf)
		error_message("ERROR: problems callocing img buffer");
	y = 0;
	while (y < data->textinfo->size)
	{
		x = 0;
		while (x < data->textinfo->size)
		{
			buf[y * data->textinfo->size + x] = \
				tmp->img_addr[y * data->textinfo->size + x];
			++x;
		}
		++y;
	}
	mlx_destroy_image(data->mlx_conn, tmp->img);
	free(tmp);
	return (buf);
}

//Function to initialize the textures (NORTH< SOUTH, WEST, EAST)
//it allocate memory for the textures and call the put img into buffer function
//to load the textures in the data structure
int	ft_initialize_textures(t_data *data)
{
	data->texture_pixels = ft_calloc(4, sizeof(int *));
	if (!data->texture_pixels)
		error_message("ERROR: problems callocing texture pixels");
	data->texture_pixels[N] = ft_put_img_into_buffer(data, data->textinfo->north);
	if (!data->texture_pixels[N])
		error_message("ERROR: problem loading N texture");
/*	data->texture_pixels[S] = ft_put_img_into_buffer(data, data->textinfo->south);
	if (!data->texture_pixels[S])
		error_message("ERROR: probelm loading S texture");
	data->texture_pixels[E] = ft_put_img_into_buffer(data, data->textinfo->east);
	if (!data->texture_pixels[E])
		error_message("ERROR: problem loading E texture");
	data->texture_pixels[W] = ft_put_img_into_buffer(data, data->textinfo->west);
	if (!data->texture_pixels[W])
		error_message("ERROR: problem loading W texture");*/
	return (EXIT_SUCCESS);
}
