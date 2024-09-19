/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:52:09 by luifer            #+#    #+#             */
/*   Updated: 2024/09/19 17:45:35 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//Function to initialize the image, it will initialize an empty image structure
//create the new image using the mlx library and check that was correctly created
//assign the image address
int	ft_initialize_imginfo(t_data *data)
{
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

//Function to put the converted xpm image into an integer buffer
//use this function if we need to manipulate the image at all
//otherwise, use the mlx_xpm_file_to_image function as it is more
//efficient
/*int	*ft_put_img_into_buffer(t_data *data, char *path)
{
	int		*buf;
	int		x;
	int		y;

	if (ft_initialize_texture_image(data, &data->imginfo, path) == EXIT_FAILURE)
		error_message("ERROR: problems initializing texture image\n");
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
				data->imginfo->img_addr[y * data->textinfo->size + x];
			++x;
		}
		++y;
	}
	mlx_destroy_image(data->mlx_conn, data->imginfo);
	return (buf);
}*/

//Function to initialize the textures (NORTH< SOUTH, WEST, EAST)
//it allocate memory for the textures and call the put img into buffer function
//to load the textures in the data structure
int	ft_initialize_textures(t_data *data)
{
//	data->textures = ft_calloc(4, sizeof(int *));
//	if (!data->textures)
//		error_message("ERROR: problems callocing texture pixels");
//	data->textures[N] = ft_put_img_into_buffer(data, data->textinfo->north);
	data->textures[N] = mlx_xpm_file_to_image(data->mlx_conn, data->textinfo->north, &data->image_width, &data->image_height);
	if (!data->textures[N])
	{
		printf("Error loading texture: %s\n", data->textinfo->north);
		mlx_destroy_window(data->mlx_conn, data->mlx_window);
		mlx_destroy_display(data->mlx_conn);
		free(data->mlx_conn);
		return (1);	
	}
	mlx_put_image_to_window(data->mlx_conn, data->mlx_window, data->textures[0], 0, 0);
//		error_message("ERROR: problem loading N texture");
/*	data->textures[E] = ft_put_img_into_buffer(data, data->textinfo->east);
	if (!data->textures[E])
		error_message("ERROR: problem loading E texture");
	data->textures[S] = ft_put_img_into_buffer(data, data->textinfo->south);
	if (!data->textures[S])
		error_message("ERROR: probelm loading S texture");
	data->textures[W] = ft_put_img_into_buffer(data, data->textinfo->west);
	if (!data->textures[W])
		error_message("ERROR: problem loading W texture");*/
	return (EXIT_SUCCESS);
}

void	check_path(char *path)
{
	if (access(path, F_OK) == -1)
	{
		printf("ERROR: path not found or accessible: %s\n", path);
		exit(EXIT_FAILURE);
	}
}
