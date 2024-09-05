/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:52:09 by luifer            #+#    #+#             */
/*   Updated: 2024/09/05 14:16:15 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//Function to initialize the image, it will initialize an empty image structure
//create the new image using the mlx library and check that was correctly created
//assign the image address
int	ft_initialize_image(t_data *data, t_img *image, int width, int height)
{
	printf("in init window\n");
	ft_initialize_img(image);
	image->img = mlx_new_image(data->mlx_conn, width, height);
	if (!image->img)
		return (EXIT_FAILURE);
	image->img_addr = (int *)mlx_get_data_addr
		(image->img, &image->bpp, &image->line_len, &image->endian);
	if (!image->img_addr)
		return (EXIT_FAILURE);
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
		return (EXIT_FAILURE);
	data->mlx_window = mlx_new_window(data->mlx_conn, data->window_height, data->window_width, "Cub3D");
	if (!data->mlx_window)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

//Function to initialize the textures into the image structure
//it will load the xmp file into an image and get the data address
int	ft_initialize_texture_img(t_data *data, t_img *image, char *path)
{
	ft_initialize_image(data, image, WIDTH, HEIGHT);
	image->img = mlx_xpm_file_to_image(data->mlx_conn, path, &data->window_width, &data->window_height);
	if (!image->img)
		return (EXIT_FAILURE);
	image->img_addr = (int *)mlx_get_data_addr
		(image->img, &image->bpp, &image->line_len, &image->endian);
	if (!image->img_addr)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

//Function to put the converted xpm image into an integer buffer
//it load the
int	*ft_put_img_into_buffer(t_data *data, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	ft_initialize_texture_img(data, &tmp, path);
	buffer = ft_calloc(1, sizeof(*buffer) * data->textinfo->size * data->textinfo->size);
	if (!buffer)
		ft_malloc_error();
	y = 0;
	while (y < data->textinfo->size)
	{
		x = 0;
		while (x < data->textinfo->size)
		{
			buffer[y * data->textinfo->size + x] = (&tmp)->img_addr[y * data->textinfo->size + x];
			++x;
		}
		++y;
	}
	mlx_destroy_image(data->mlx_conn, tmp.img);
	return (buffer);
}

//Function to initialize the textures (NORTH< SOUTH, WEST, EAST)
//it allocate memory for the textures and call the put img into buffer function
//to load the textures in the data structure
int	ft_initialize_textures(t_data *data)
{
	data->textures = ft_calloc(5, sizeof * data->textures);
	if (!data->textures)
		return (EXIT_FAILURE);
	data->textures[N] = ft_put_img_into_buffer(data, data->textinfo->north);
	data->textures[S] = ft_put_img_into_buffer(data, data->textinfo->south);
	data->textures[E] = ft_put_img_into_buffer(data, data->textinfo->east);
	data->textures[W] = ft_put_img_into_buffer(data, data->textinfo->west);
	return (EXIT_SUCCESS);
}

