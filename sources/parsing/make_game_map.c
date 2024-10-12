/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_game_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:56:28 by kbolon            #+#    #+#             */
/*   Updated: 2024/10/12 17:05:00 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_change_space(t_data *data)
{
	int		y;
	size_t	x;
	char	**new_map;

	y = -1;
	data->mapinfo->map_width = ft_find_longest_line(data->textinfo->grid);
	new_map = reallocate_map(data, data->mapinfo->map_width);
	if (!new_map)
		exit(EXIT_FAILURE);
//	free_memory(data->map);
	data->map = new_map;
	while (data->map[++y])
	{
		x = 0;
		while (data->map[y][x] && x < data->mapinfo->map_width)
		{
			if (data->map[y][x] == ' ' || data->map[y][x] == '\r' ||\
				data->map[y][x] == '\t' || data->map[y][x] == '\v')
			{
				data->map[y][x] = '1';
			}
			x++;
		}
	}
}

int	ft_make_game_map(t_data *data)
{
	ft_change_space(data);
	if (!data->map)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_find_longest_line(char **arr)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	count = 0;
	while (arr[y])
	{
		x = ft_strlen(arr[y]);
		if (count < x)
			count = x;
		y++;
	}
	return (count);
}

char	**reallocate_map(t_data *data, int len)
{
	char	**new;
	int		current_len;
	size_t	i;

	new = (char **)ft_calloc(data->mapinfo->map_height + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < data->mapinfo->map_height)
	{
		new[i] = (char *)malloc((len + 1) * sizeof(char));
		if (!new[i])
			free_partial((void **)new, i);
		ft_strncpy(new[i], data->textinfo->grid[i], len);
		current_len = ft_strlen(data->textinfo->grid[i]);
		while (current_len < len)
		{
			new[i][current_len] = '1';
			current_len++;
		}
		new[i][len] = '\0';
	}
	new[data->mapinfo->map_height] = NULL;
	return (new);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
