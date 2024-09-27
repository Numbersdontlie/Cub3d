/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:56:52 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/27 14:11:47 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

//function loads the game image (renders floor and ceiling
//raycasts to render walls and displays final image)
int	ft_game(t_data *data)
{
	mlx_clear_window(data->mlx_conn, data->mlx_window);
	ft_render_ceiling_and_floor(data);
	ft_make_raycasting(data->player, data);
	mlx_put_image_to_window(data->mlx_conn, data->mlx_window, data->img_FC->img, 0, 0);
//	ft_render_scene(data);
	return (EXIT_SUCCESS);
}

//function splits the screen into two parts and 
//extracts colours for floor and ceiling
/*void	ft_render_ceiling_and_floor(t_data *data)
{
	data->img_FC = (t_img *)ft_calloc(1, sizeof(t_img));
	if (!data->img_FC)
		error_exit("ERROR: calloc failed in floor/ceiling\n", data, NULL);
	data->img_FC->img = mlx_new_image(data->mlx_conn, WIDTH, HEIGHT);
	if (!data->img_FC->img)
		error_exit("ERROR: Failed to load floor img\n", data, NULL);
	data->img_FC->img_addr = mlx_get_data_addr(data->img_FC->img, \
		&data->img_FC->bpp, &data->img_FC->line_len, &data->img_FC->endian);
	if (!data->img_FC->img_addr)
		error_exit("ERROR: failure to get floor address\n", data, NULL);
	mlx_put_image_to_window(data->mlx_conn, data->mlx_window, data->img_FC->img, 0, 0);
}*/

/*void	ft_render_scene(t_data *data)
{
	int	y;
	int	x;
	int	pix;
	int	texture_pix;
	
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		{
			while (++x < WIDTH)
			{
				if (y < HEIGHT/2)
					pix = data->textinfo->hex_ceiling;
				else if (y >= HEIGHT / 2 && y < HEIGHT)
					pix = data->textinfo->hex_floor;
				else
				{
					ft_calculate_texture_coords(data, data->ray);  // Calculate texture coords
					ft_render_texture(data, (int *)data->imginfo[data->textinfo->idx]->img_addr, data->ray, x);
				}
				if (pix > 0)
					ft_put_pixel_to_img(data->img_FC, x, y, pix);
				else if (texture_pix > 0)
					ft_put_pixel_to_img(data->imginfo[data->ray->side], x, y, texture_pix);
			}
		}
	}
}*/

//function splits the screen into two parts and 
//extracts colours for floor and ceiling
void	ft_render_ceiling_and_floor(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	data->img_FC = (t_img *)ft_calloc(1, sizeof(t_img));
	if (!data->img_FC)
		error_exit("ERROR: calloc failed in floor/ceiling\n", data, NULL);
	while (++y < HEIGHT)
	{
		x = -1;
		{
			while (++x < WIDTH)
			{
				if (y < HEIGHT/2)
					ft_put_pixel_to_img(data->img_FC, x, y, \
						data->textinfo->hex_ceiling);
				else
					ft_put_pixel_to_img(data->img_FC, x, y, \
						data->textinfo->hex_floor);
			}
		}
	}
}

void	ft_put_pixel_to_img(t_img *imginfo, int x, int y, int colour)
{
	char	*pixel;

	pixel = (char *)imginfo->img_addr + (y * imginfo->line_len + x * \
		imginfo->bpp/8);
	*(unsigned int *)pixel = colour;
}
