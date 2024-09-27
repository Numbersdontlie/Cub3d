/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderV2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:25:59 by luifer            #+#    #+#             */
/*   Updated: 2024/09/27 13:33:27 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../../includes/cub3D.h"

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
