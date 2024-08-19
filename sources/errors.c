/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:47:58 by kbolon            #+#    #+#             */
/*   Updated: 2024/08/19 11:30:22 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	error_message(char *str, int code)
{
	ft_putstr_fd(str, 2);
	return (code);
}

int	error_input()
{
	ft_putstr_fd("Error: Please include minimum ./cub3D and .cub file\n\n", 2);
	ft_putstr_fd("Other input **NOTE** .cub must be last input ALWAYS:", 2);
	ft_putstr_fd("\nNO ./path_to_north_texture\n", 2);
	ft_putstr_fd("SO ./path_to_south_texture\n", 2);
	ft_putstr_fd("WE ./path_to_west_texture\n", 2);
	ft_putstr_fd("EA ./path_to_east_texture\n", 2);
	ft_putstr_fd("RGB colour in range of 0-255 for F and C\n", 2);
	ft_putstr_fd("example: F 125.125.125, C 175.125.255\n", 2);
	return (2);
}
