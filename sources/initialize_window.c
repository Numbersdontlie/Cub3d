/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:52:09 by luifer            #+#    #+#             */
/*   Updated: 2024/08/19 22:33:52 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3D.h"

//Function to initialize the image, it will initialize an empty image structure
//create the new image using the mlx library and check that was correctly created
//assign the image address
void	ft_initialize_image(t_data *data, t_img *image, int width, int height)
{
	ft_initialize_img(image);
	image->img = mlx_new_image(data->mlx_conn, width, height);
	if (!image->img)
		ft_clean_exit();//ToDo
	image->img_addr = (int *)mlx_get_data_addr(image->img, image->bpp, image->line_len, image->endian);
	return ;
}

//Function to initialize the connection with the minilibx library
//it creates a connection with the library and creates a window
//into that connection. It also check that connection and window
//where created without problem
void	ft_initialize_connection(t_data *data)
{
	data->mlx_conn = mlx_init();
	if (!data->mlx_conn)
		ft_clean_exit();//ToDo
	data->mlx_window = mlx_new_window(data->mlx_conn, WIDTH, HEIGHT, "Cub3D");
	if (!data->mlx_window)
		ft_clean_exit();//ToDo
	return ;
}

//Function to initialize the textures
void	ft_initialize_texture_img(t_data *data, t_img *image, char *path)
{

}