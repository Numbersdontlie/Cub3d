/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:56:52 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/28 10:36:41 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

//function loads the game image (renders floor and ceiling
//raycasts to render walls and displays final image)
int	ft_launch_game(t_data *data)
{

	data->img = mlx_new_image(data->mlx_conn, WIDTH, HEIGHT);
	data->img->img_addr = (int *)mlx_get_data_addr(data->img, &data->img->bpp, &data->img->line_len, &data->img->endian);
	ft_render_ceiling_and_floor(data);
	ft_make_raycasting(data->player, data);
	ft_move_player(data);
	mlx_put_image_to_window(data->mlx_conn, data->mlx_window, data->img->img, 0, 0);
	mlx_destroy_image(data->mlx_conn, data->img->img);
	return (EXIT_SUCCESS);
}



//function splits the screen into two parts and 
//extracts colours for floor and ceiling
int	ft_render_ceiling_and_floor(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (y < HEIGHT/2)
				ft_put_pixel_to_img(data->img, x, y, \
					data->textinfo->hex_ceiling);
			else
				ft_put_pixel_to_img(data->img, x, y, \
					data->textinfo->hex_floor);
		}
	}
	return (EXIT_SUCCESS);
}

void	ft_put_pixel_to_img(t_img *imginfo, int x, int y, int colour)
{
	char	*pixel;

	if (!imginfo || !imginfo->img_addr)
		return ;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = (char *)imginfo->img_addr + (y * imginfo->line_len + x * \
		(imginfo->bpp/8));
	*(unsigned int *)pixel = colour;
}
