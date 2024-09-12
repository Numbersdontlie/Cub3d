/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:52:09 by luifer            #+#    #+#             */
/*   Updated: 2024/09/12 16:47:28 by kbolon           ###   ########.fr       */
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

void	check_file_exists(t_data *data)
{

	if (access(data->textinfo->north, F_OK) != 0)
		error_message_data("ERROR: path to N texture not valid", data, NULL);
	if (access(data->textinfo->south, F_OK) != 0)
		error_message_data("ERROR: path to S texture not valid", data, NULL);
	if (access(data->textinfo->west, F_OK) != 0)
		error_message_data("ERROR: path to W texture not valid", data, NULL);
	if (access(data->textinfo->east, F_OK) != 0)
		error_message_data("ERROR: path to E texture not valid", data, NULL);
}

//Function to initialize the connection with the minilibx library
//it creates a connection with the library and creates a window
//into that connection. It also check that connection and window
//where created without problem
int	ft_initialize_connection(t_data *data)
{
	printf("in connections\n");
	data->mlx_conn = mlx_init();
	if (!data->mlx_conn)
		error_message_data("ERROR: problem initiating connection\n", data, NULL);
	data->mlx_window = mlx_new_window(data->mlx_conn, data->window_height, \
		data->window_width, "Cub3D");
	if (!data->mlx_window)
		error_message_data("ERROR: problem initiating window\n", data, NULL);
	printf("out connections\n");
	return (EXIT_SUCCESS);
}

//Function to initialize the textures into the image structure
//it will load the xmp file into an image and get the data address
int	ft_initialize_texture_img(t_data *data, t_img **image, char *path)
{
	int		*address;

	*image = (t_img *)ft_calloc(1, sizeof(t_img));
	if (!(*image))
		error_message_data("ERROR: problem callocing img\n", data, NULL);
//
	printf("Loading texture from path: %s\n", path);
	(*image)->img = mlx_xpm_file_to_image(data->mlx_conn, path, \
		&data->window_width, &data->window_height);
	if (!(*image)->img)
		error_message_data("ERROR: problem initiating texture1\n", data, NULL);
	address = (int *)mlx_get_data_addr
		((*image)->img, &(*image)->bpp, &(*image)->line_len, &(*image)->endian);
	(*image)->img_addr = address;
	if (!(*image)->img_addr)
		error_message_data("ERROR: problem initiating image address\n", \
			data, NULL);
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
	data->textures = ft_calloc(4, sizeof(int *));
	if (!data->textures)
		error_message_data("ERROR: problems callocing textures", data, NULL);
	data->textures[N] = ft_put_img_into_buffer(data, data->textinfo->north);
	if (!data->textures[N])
		error_message_data("ERROR: problem loading N texture", data, NULL);
	data->textures[S] = ft_put_img_into_buffer(data, data->textinfo->south);
	if (!data->textures[S])
		error_message_data("ERROR: probelm loading S texture", data, NULL);
	data->textures[E] = ft_put_img_into_buffer(data, data->textinfo->east);
	if (!data->textures[E])
		error_message_data("ERROR: problem loading E texture", data, NULL);
	data->textures[W] = ft_put_img_into_buffer(data, data->textinfo->west);
	if (!data->textures[W])
		error_message_data("ERROR: problem loading W texture", data, NULL);
	return (EXIT_SUCCESS);
}
