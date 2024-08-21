/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:42:05 by kbolon            #+#    #+#             */
/*   Updated: 2024/08/21 15:37:13 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	valid_chars(char **arr)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (arr[i] != NULL)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			if (ft_strchr("01NSEW\n", arr[i][j]))
				j++;
			else
				error_message_simple("ERROR: illegal character in map", arr);
		}
		i++;
	}
}

void	count_chars(char **arr, size_t *player)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (arr[i] != NULL)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			if (arr[i][j] == 'N' || arr[i][j] == 'S' || \
				arr[i][j] == 'W' || arr[i][j] == 'E')
				(*player) += 1;
			j++;
		}
		i++;
	}
}

void	check_map_items(char **arr)
{
	size_t		player;

	player = 0;
	count_chars(arr, &player);
	if (player != 1)
		error_message_simple("ERROR: Map not valid, check content", arr);
}

