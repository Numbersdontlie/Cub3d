/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:02:47 by luifer            #+#    #+#             */
/*   Updated: 2024/09/26 06:50:39 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

/*****I COMMENTED OUT BECAUSE IT MADE ERRORS WITH THE TVECTOR*****


//Function to apply the rotation formula
static void	ft_rotate(t_vector *vector, double speedrot)
{
	double	old_x;

	old_x = vector->x;
	vector->x = vector->x * cos(speedrot) - vector->y * sin(speedrot);
	vector->y = old_x * sin(speedrot) + vector->y * cos(speedrot);
}

//Function to rotate the player direction vector
//the direction vector (dir_x, dir_y) is rotated by the angle speedrot
//the new values for dir_x an dir_y are calculated using 2D rotation formulas
//it also rotate the camera plane (plane_x, plane_y) by the angle speedrot
//using the same rotation formula
int	ft_rotate_player_dir_vector(t_data *data, double speedrot)
{
	t_player	*ply;
	t_vector	*tmp;

	tmp = NULL;
	ply = data->player;
	tmp = {ply->dir_x, ply->dir_y};
	ft_rotate(tmp, speedrot);
	tmp = {ply->plane_x, ply->plane_y};
	ft_rotate(tmp, speedrot);
	return (EXIT_FAILURE);
}

//Function to execute the rotation of the player in engine
int	ft_execute_rotation(t_data *data, double dirrot)
{
	int		move;
	double	speed_rotation;

	move = 0;
	speed_rotation = ROTATIONSPEED * dirrot;
	move += ft_rotate_player_dir_vector(data, speed_rotation);
	return (move);
}*/
