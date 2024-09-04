/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:49:35 by lperez-h          #+#    #+#             */
/*   Updated: 2024/09/04 14:57:28 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

//Function to get the texture index from the textinfo struct
//if side is not zero, we're working on the y axis, else on the x
//if y axis if dir_y is greather than zero then we're on South 
//else North. If x axis is lower than zero is west else east
void	ft_get_texture_idx(t_data *data, t_ray *ray)
{
	if (ray->side != 0)
	{
		if (ray->dir_y > 0)
			data->textinfo.idx = S;
		else
			data->textinfo.idx = N;
	}
	else
	{
		if (ray->dir_x < 0)
			data->textinfo.idx = W;
		else
			data->textinfo.idx = E;
	}
}
