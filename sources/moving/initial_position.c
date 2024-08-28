/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_position.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:36:47 by lperez-h          #+#    #+#             */
/*   Updated: 2024/08/28 15:47:26 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

//Function to initialize the player direction
//if player is looking to the north it will be initialized to north
//else to the south
void	ft_initialize_nort_sout(t_player *player)
{
	if (player->direction == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (player->direction == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else
		return ;
}

//Function to initialize the player direction
//if player is looking to the east it will be initialized to east
//else to the west
void	ft_initialize_weast_east(t_player *player)
{
	if (player->direction == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (player->direction == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0;
	}
	else
		return ;
}

void	ft_init_player_dir(t_data *data)
{
	ft_initialize_nort_sout(&data->player);
	ft_initialize_weast_east(&data->player);
}