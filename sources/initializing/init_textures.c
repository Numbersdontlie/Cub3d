/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:30:58 by kbolon            #+#    #+#             */
/*   Updated: 2024/10/09 10:54:40 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


int		*xpm_buffer_image(t_data *data, char *path)
{
	t_img	temp;
	int		*buff;
	int		x;
	int		y;

	ft_init_texture_img(data, &temp, path);
	buff = ft_calloc((temp.texture_width * temp.texture_height), sizeof(int));
	if (!buff)
		return (0);
	y = 0;
	while (y < PIXELS)
	{
		x = 0;
		while (x < PIXELS)
		{
			buff[y * PIXELS + x] = temp.img_addr[y * PIXELS + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(data->mlx_conn, temp.img);
	return (buff);
}

//Function to initialize the image, it creates the new image using 
//the mlx library and checks it was correctly created and saves the image address
int	ft_initialize_textures(t_data *data)
{
	int		i;

	i = 0;
	data->textures = ft_calloc(5, sizeof(int *));//4 work???
	if (!data->textures)
		return (EXIT_FAILURE);
	while (data->textinfo->paths[i])
	{
		data->textures[i] = *xpm_buffer_image(data, data->textinfo->paths[i]);
		if (!data->textures[i])
		{
			printf("Error loading textures in ft_initialize_textures\n");//change
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
