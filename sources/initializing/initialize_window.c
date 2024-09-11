/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:52:09 by luifer            #+#    #+#             */
/*   Updated: 2024/09/11 19:46:32 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//Function to initialize the image, it will initialize an empty image structure
//create the new image using the mlx library and check that was correctly created
//assign the image address
int	ft_initialize_image(t_data *data, t_img **image, int width, int height)
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
int	ft_initialize_texture_img(t_data *data, t_img **image, char *path)
{
	*image = (t_img *)ft_calloc(1, sizeof(t_img));
	if (!(*image))
		return (EXIT_FAILURE);
//	if (ft_initialize_image(data, &image, WIDTH, HEIGHT) == EXIT_SUCCESS)
//	{
	(*image)->img = mlx_xpm_file_to_image(data->mlx_conn, path, &data->window_width, &data->window_height);
	if (!(*image)->img)
		return (EXIT_FAILURE);
	(*image)->img_addr = (int *)mlx_get_data_addr((*image)->img, &(*image)->bpp, &(*image)->line_len, &(*image)->endian);
	if (!(*image)->img_addr)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

//Function to put the converted xpm image into an integer buffer
//it load the
int	*ft_put_img_into_buffer(t_data *data, char *path)
{
	t_img	*tmp;
	int		*buf;
	int		x;
	int		y;

	tmp = NULL;
	if (ft_initialize_texture_img(data, &tmp, path) == EXIT_FAILURE)
	{
		free (path);
		error_message_data("ERROR: problems initializing textures", data, NULL);
	}
	buf = ft_calloc(data->textinfo->size * data->textinfo->size, sizeof(int));
	if (!buf)
		error_message_data("ERROR: problems callocing img buffer", data, NULL);
	y = 0;
	while (y < data->textinfo->size)
	{
		x = 0;
		while (x < data->textinfo->size)
		{
			buf[y * data->textinfo->size + x] = tmp->img_addr[y * data->textinfo->size + x];
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
	data->textures = ft_calloc(4, sizeof(int *));
	if (!data->textures)
		return (EXIT_FAILURE);
	data->textures[N] = ft_put_img_into_buffer(data, data->textinfo->north);
	if (!data->textures[N])
		return (EXIT_FAILURE);
	data->textures[S] = ft_put_img_into_buffer(data, data->textinfo->south);
	if (!data->textures[S])
		return (EXIT_FAILURE);
	data->textures[E] = ft_put_img_into_buffer(data, data->textinfo->east);
	if (!data->textures[E])
		return (EXIT_FAILURE);
	data->textures[W] = ft_put_img_into_buffer(data, data->textinfo->west);
	if (!data->textures[W])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

