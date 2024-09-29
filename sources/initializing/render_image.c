/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:56:52 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/29 10:59:53 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

//function loads the game image (renders floor and ceiling
//raycasts to render walls and displays final image)
int	ft_launch_game(t_data *data)
{
//	data->img = mlx_new_image(data->mlx_conn, WIDTH, HEIGHT);
//	data->img->img_addr = (int *)mlx_get_data_addr(data->img, &data->img->bpp, &data->img->line_len, &data->img->endian);
	ft_render_background(data);
//	ft_make_raycasting(data->player, data);
//	ft_move_player(data);
	mlx_put_image_to_window(data->mlx_conn, data->mlx_window, data->background.img, 0, 0);
	mlx_destroy_image(data->mlx_conn, data->background.img);
	return (EXIT_SUCCESS);
}



//function splits the screen into two parts and 
//extracts colours for floor and ceiling
void	ft_render_background(t_data *data)
{
	int				x;
	int				y;
	unsigned long	colour;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (y < HEIGHT/2)
			{
				colour = data->textinfo->hex_ceiling;
				 *(unsigned int *)(data->background.img_addr + (y * data->background.line_len + x * (data->background.bpp / 8))) = colour;
//				ft_put_pixel_to_img(data->background, x, y, \
//					data->textinfo->hex_ceiling);
			}
			else
			{
				colour = data->textinfo->hex_floor;
				*(unsigned int *)(data->background.img_addr + (y * data->background.line_len + x * (data->background.bpp / 8))) = colour;
//				ft_put_pixel_to_img(data->background, x, y, \
//					data->textinfo->hex_floor);
			}
		}
	}
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
//Function to render the game, it will check if the player
//has moved and update the player new position accordingly
//the raycast is render after this verification
int	ft_render(t_data *data)
{
	int	move;

	move = data->player->has_moved;
	move += ft_move_player(data);
	if (move == 0)
		return (EXIT_SUCCESS);
	ft_make_raycasting(data->player, data);
//	ft_draw_image_in_window(data);
	return (EXIT_SUCCESS);
}