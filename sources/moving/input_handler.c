/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:53:26 by luifer            #+#    #+#             */
/*   Updated: 2024/09/04 16:54:28 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//Function to handle the input from the keyboard
//Escape close the program, WSAD move the player position
//left and right arrow change the point of view (rotation)
int	ft_handle_key(int keysym, t_data *data)
{
	if (keysym == XK_ESCAPE)
		ft_clean_exit(data);
	if (keysym == LEFT)
		data->player.rotate -= 1;
	if (keysym == RIGHT)
		data->player.rotate += 1;
	if (keysym == FORWARD)
		data->player.move_y = 1;
	if (keysym == BACKWARD)
		data->player.move_y = -1;
	if (keysym == ROTATE_LEFT)
		data->player.move_x = -1;
	if (keysym == ROTATE_RIGHT)
		data->player.move_x = 1;
	return (0);
}

//Function to handle the release of the key after being 
//hold pressed for a while
int	ft_release_key(int keysym, t_data *data)
{
	if (keysym == XK_ESCAPE)
		ft_clean_exit(data);
	if (keysym == LEFT)
		data->player.rotate -= 1;
	if (keysym == RIGHT)
		data->player.rotate += 1;
	if (keysym == FORWARD)
		data->player.move_y = 1;
	if (keysym == BACKWARD)
		data->player.move_y = -1;
	if (keysym == ROTATE_LEFT)
		data->player.move_x = -1;
	if (keysym == ROTATE_RIGHT)
		data->player.move_x = 1;
	return (0);
}


/*void	ft_initialize_events(t_data *data)
{
	mlx_hook(data->mlx_window, KeyPress, KeyPressMask, ft_handle_key, data);
	mlx_hook(data->mlx_window, DestroyNotify, StructureNotifyMask, ft_clean_exit, data);
	mlx_hook(data->mlx_window, KeyRelease, KeyReleaseMask, ft_release_key, data);
	//We're missing the hook to handle the input from mouse if we make the bonus
}*/